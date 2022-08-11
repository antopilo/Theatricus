#pragma once
#include <NuakeRenderer/Texture.h>
using namespace NuakeRenderer;

#include <map>
#include <string>
#include <variant>

using Input = std::variant<bool, int, double, float, Vector2, Vector3, Vector4>;

enum class InputTypes
{
	Bool, Int, Double, Float, Vector2, Vector3, Vector4, Texture
};

class Node
{
private:

public:
	Node() = default;
	~Node() = default;

	// inputs
	std::map<std::string, InputTypes> _inputTypes;
	std::map<std::string, Input> _inputData;

	// outputs
	std::map<std::string, Input> _outputs;

	// Declares all the input and outputs as well as the constraints.
	virtual void Register() {};

	// Sets the outputs and do processing of inputs.
	virtual void Process() {};

	void RegisterInput(const std::string name, const InputTypes& inputType)
	{
		_inputTypes[name] = inputType;
	}

	template<typename T>
	void SetInput(const std::string& inputName, T&& input)
	{
		_inputData[inputName] = std::move(input);
	}

	template<typename T>
	bool GetInput(const std::string& inputName, T& input)
	{
		if (!HasInput(inputName))
		{
			return false;
		}

		const InputTypes& type = _inputTypes[inputName];
		if (!VerifyTemplateTypeMismatch<T>(type))
		{
			assert(false && "Type mismatch");
		}

		input = &std::get<T>(_inputData[inputName]);
		return true;
	}

	bool HasInput(const std::string& inputName)
	{
		return _inputData.find(inputName) != _inputData.end();
	}
private:
	template<typename T>
	bool VerifyTemplateTypeMismatch(const InputTypes& inputType)
	{
		return false;
	}

	template<>
	bool VerifyTemplateTypeMismatch<bool>(const InputTypes& inputType)
	{
		return inputType == InputTypes::Bool;
	}

	template<>
	bool VerifyTemplateTypeMismatch<int>(const InputTypes& inputType)
	{
		return inputType == InputTypes::Int;
	}
};

class RedNode : public Node
{
public:
	RedNode() = default;
	~RedNode() = default;

	// Declare nodes inputs, outputs
	void Register() override
	{
		RegisterInput("InputBool", InputTypes::Bool);
		//RegisterInput("InputInt", InputTypes::Int);
	}

	void Process() override
	{
		// I want a texture as output.
		bool boolInput;
		if (GetInput<bool>("InputBool", boolInput))
		{
			boolInput = !boolInput;
			// Sets outputs values.

			boolInput = !boolInput;
		}
	}
};