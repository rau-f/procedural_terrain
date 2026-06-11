#include "include/shaders.h"
#include <vector>


std::string getFileContent(const char* fileName)
{
    std::ifstream in(fileName, std::ios::in);
    if(in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    throw std::runtime_error("Failed to open file!");
}


void Shader::CreateShader(const char* vertexShaderFile, const char* fragShaderFile)
{
    std::string vertexCode = getFileContent(vertexShaderFile);
    std::string fragCode = getFileContent(fragShaderFile);

    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragCode.c_str();

    GLCall(unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER));
    GLCall(glShaderSource(vertexShader, 1, &vertexShaderSource, NULL));
    GLCall(glCompileShader(vertexShader));
    CompileStatus(vertexShader);

    GLCall(unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
    GLCall(glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL));
    GLCall(glCompileShader(fragmentShader));
    CompileStatus(fragmentShader);

    m_ID = glCreateProgram();
    GLCall(glAttachShader(m_ID, vertexShader));
    GLCall(glAttachShader(m_ID, fragmentShader));
    GLCall(glLinkProgram(m_ID));

    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));
}


unsigned int Shader::getID() const
{
    return m_ID;
}


void Shader::Bind() const
{
    GLCall(glUseProgram(m_ID));
}


void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}


void Shader::Delete() const 
{
    GLCall(glDeleteShader(m_ID));
}


void Shader::CompileStatus(unsigned int shader)
{
    int result;
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

        std::vector<char> message(length);
        GLCall(glGetShaderInfoLog(shader, length, &length, message.data()));

        int type;
        GLCall(glGetShaderiv(shader, GL_SHADER_TYPE, &type));

        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << message.data() << std::endl;
    }
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}


void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}


void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}


void Shader::SetMat4(const std::string& name, float* value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value);
}


void Shader::SetVec3(const std::string& name, const float* value)
{
    glUniform3fv(GetUniformLocation(name), 1, value);
}


void Shader::SetInt(const std::string &name, const int value)
{
    glUniform1i(GetUniformLocation(name), value);
}


int Shader::GetUniformLocation(const std::string& name)
{
    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1) {
        std::cout << "shader] m_ID: " << m_ID << std::endl;
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
        exit(0);
    }
    return location;
}