#pragma once

#include <glm/glm.hpp>

#include <unordered_map>
#include <string>

struct shaderProgramFile {
	std::string vertexSource;
	std::string fragmentSource;
};

class shader {
public:
	shader(const std::string& filepath);
	~shader();

public:
	void bind() const;
	void unbind() const;

public:
	void setUniform1i(const std::string& name, int v0);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1iv(const std::string& name, size_t i, const int *v1);
	void setUniformMat4f(const std::string& name, glm::mat4 &matrix);

private:
	shaderProgramFile parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	int getUniformLocation(const std::string &name);

private:
	std::unordered_map<std::string, int> _uniformLocationCache;
	std::string _filepath;
	unsigned int _progId;
};
