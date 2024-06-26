#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <ranges>

typedef std::pair<float, float> vec2;

constexpr std::string_view cwd =
    "C:\\Code\\Game-Engine\\tengin\\tengin\\src\\resources\\modelsRaw";
const std::string outputPath =
    "C:\\Code\\Game-Engine\\tengin\\tengin\\src\\resources\\models\\";

const std::vector<std::string> splitStr(const std::string& str,
                                        const char& delimeter);
const std::vector<float> stringToFloatVec(
    const std::vector<std::string>& strVec);
std::vector<vec2> getHitbox(const std::vector<float>& vertices);

int main() {
  std::filesystem::current_path(std::filesystem::path(cwd));
  std::filesystem::directory_iterator a(std::filesystem::current_path()), b;
  std::vector<std::filesystem::path> paths(a, b);

  std::ifstream ins;
  std::ofstream outs;

  for (int i = 0; i < paths.size(); i += 2) {
    const std::string mtlPath = paths[i].generic_string();
    const std::string objPath = paths[i + 1].generic_string();
    const std::string modelName =
        mtlPath.substr(cwd.size() + 1, mtlPath.size() - cwd.size() - 5);

    ins.open(objPath);
    outs.open(std::string(outputPath) + modelName + ".hpp");
    std::stringstream objStream;
    std::string line;

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> uv;
    std::vector<unsigned int> vertexIndices, normalIndices, uvIndices;

    objStream << ins.rdbuf();
    while (getline(objStream, line)) {
      const std::vector<std::string> tokens = splitStr(line, ' ');
      const std::string_view label(tokens[0].data(), tokens[0].size());

      if (label == "f") {
        for (int i = 1; i < 4; ++i) {
          std::vector<std::string> indices = splitStr(tokens[i], '/');
          vertexIndices.push_back(std::stoi(indices[0]));
          uvIndices.push_back(std::stoi(indices[1]));
          normalIndices.push_back(std::stoi(indices[2]));
        }
      } else if (label == "v" || label == "vn" || label == "vt") {
        const std::vector<float> currNums = stringToFloatVec(
            std::vector<std::string>{tokens.begin() + 1, tokens.end()});
        if (label == "v") {
          vertices.insert(vertices.end(), currNums.begin(), currNums.end());
        } else if (label == "vn") {
          normals.insert(normals.end(), currNums.begin(), currNums.end());
        } else if (label == "vt") {
          uv.insert(uv.end(), currNums.begin(), currNums.end());
        }
      }
    }

    const std::vector<vec2> hitbox = getHitbox(vertices);

    outs << "#pragma once\n\n#include <glm/glm.hpp>\n\n#include <vector>\n\n";
    outs << "class " << modelName << " {\n";
    outs << " public:\n";
    outs << "  const std::vector<glm::vec2> hitbox = {";
    for(const vec2& pt: hitbox) {
      outs << "\n      {" << pt.first << ", " << pt.second <<  "},";
    }
    outs << "\n  };\n";
    outs << "  const std::vector<float> vertices = {";
    for (int j = 0; j < vertices.size(); ++j) {
      if (j % 3 == 0) outs << "\n      ";
      outs << vertices[j] << ", ";
    }
    outs << "\n  };\n";
    outs << "  const std::vector<float> normals = {";
    for (int j = 0; j < normals.size(); ++j) {
      if (j % 3 == 0) outs << "\n      ";
      outs << normals[j] << ", ";
    }
    outs << "\n  };\n";
    outs << "  const std::vector<float> uv = {";
    for (int j = 0; j < uv.size(); ++j) {
      if (j % 3 == 0) outs << "\n      ";
      outs << uv[j] << ", ";
    }
    outs << "\n  };\n";
    outs << "  const std::vector<unsigned int> vertexIndices = {";
    for (int j = 0; j < vertexIndices.size(); ++j) {
      if (j % 3 == 0) outs << "\n      ";
      outs << vertexIndices[j] << ", ";
    }
    outs << "\n  };\n";
    outs << "  const std::vector<unsigned int> normalIndices = {";
    for (int j = 0; j < normalIndices.size(); ++j) {
      if (j % 3 == 0) outs << "\n      ";
      outs << normalIndices[j] << ", ";
    }
    outs << "\n  };\n";
    outs << "  const std::vector<unsigned int> uvIndices = {";
    for (int j = 0; j < uvIndices.size(); ++j) {
      if (j % 3 == 0) outs << "\n      ";
      outs << uvIndices[j] << ", ";
    }
    outs << "\n  };\n";
    outs << "};" << std::endl;

    ins.close();
    outs.close();
  }
  return 0;
}

const std::vector<std::string> splitStr(const std::string& str,
                                        const char& delimeter) {
  std::stringstream ss(str);
  std::string token;
  std::vector<std::string> tokens;

  while (getline(ss, token, delimeter)) {
    tokens.push_back(token);
  }
  return tokens;
}

const std::vector<float> stringToFloatVec(
    const std::vector<std::string>& strVec) {
  std::vector<float> res(strVec.size());
  std::transform(strVec.begin(), strVec.end(), res.begin(),
                 [](const std::string& val) { return std::stof(val); });
  return res;
}

float cross_product(vec2 O, vec2 A, vec2 B) {
  return (A.first - O.first) * (B.second - O.second) -
         (A.second - O.second) * (B.first - O.first);
}

std::vector<vec2> getHitbox(const std::vector<float>& vertices) {
  size_t k = 0, n = vertices.size() / 3;
  std::vector<vec2> points;
  std::vector<vec2> hitbox((n - 1) * 2);
  for (size_t i = 0; i < vertices.size(); i += 3) {
    points.emplace_back(vertices[i], vertices[i + 2]);
  };

  std::sort(points.begin(), points.end(), [](const vec2& l, const vec2& r) {
    return l.first < r.first || (l.first == r.first && l.second < l.second);
  });

  for (const vec2& point : points) {
    while (k >= 2 && cross_product(hitbox[k - 2], hitbox[k - 1], point) <= 0)
      k--;
    hitbox[k++] = point;
  }

  for (size_t i = n - 1, t = k + 1; i > 0; --i) {
    while (k >= t &&
           cross_product(hitbox[k - 2], hitbox[k - 1], points[i - 1]) <= 0)
      k--;
    hitbox[k++] = points[i - 1];
  }

  hitbox.resize(k);
  return hitbox;
}