#pragma once

#include <string>

class Shader {
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    unsigned int getProgramID() const;
private:
    // program ID
    unsigned int ID;
};
