#include <shader.hpp>
#include <renderer.hpp>
#include <openglError.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

shader::shader(const std::string& filepath) : _filepath(filepath), _progId(0) {
    shaderProgramFile source = parseShader(_filepath);
    //std::cout << "vertex" << std::endl << source.vertexSource << std::endl << "fragment" << std::endl << source.fragmentSource << std::endl;
    _progId = createShader(source.vertexSource, source.fragmentSource);
}

shader::~shader() {
    GLCALL(glDeleteProgram(_progId));
};

shaderProgramFile shader::parseShader(const std::string &filepath)
{
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filepath);
    std::stringstream ss[2];
    std::string line;
    ShaderType type = ShaderType::NONE;

    if (stream.is_open() == false)
        std::cout << "fail open file!" << std::endl;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            else if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
        } else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int shader::compileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    int result;

    GLCALL(glShaderSource(id, 1, &src, nullptr));
    GLCALL(glCompileShader(id));

    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        std::cerr << " Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader !" << std::endl;
        std::cerr << message << std::endl;
        GLCALL(glDeleteShader(id));
        return 0;
    }
    return id;
}

unsigned int shader::createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int prog = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCALL(glAttachShader(prog, vs));
    GLCALL(glAttachShader(prog, fs));
    GLCALL(glLinkProgram(prog));
    GLCALL(glValidateProgram(prog));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));
    return prog;
}

void shader::bind() const
{
    GLCALL(glUseProgram(_progId));
}

void shader::unbind() const
{
    GLCALL(glUseProgram(0));
}

void shader::setUniform1i(const std::string& name, int v0)
{
    GLCALL(glUniform1i(getUniformLocation(name), v0));
}

void shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void shader::setUniform1iv(const std::string& name, size_t i, const int *v1)
{
    GLCALL(glUniform1iv(getUniformLocation(name), i, v1));
}


void shader::setUniformMat4f(const std::string& name, glm::mat4& matrix)
{
    GLCALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


int shader::getUniformLocation(const std::string &name)
{
    if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
        return _uniformLocationCache[name];
    GLCALL(int location = glGetUniformLocation(_progId, name.c_str()));
    if (location == -1)
        std::cerr << "Warnning: uniform '" << name << "' dosen't exist !" << std::endl;
    _uniformLocationCache[name] = location;
    return location;
}
