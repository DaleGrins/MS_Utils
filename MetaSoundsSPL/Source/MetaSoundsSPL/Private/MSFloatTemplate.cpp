// Fill out your copyright notice in the Description page of Project Settings.


#include "MSFloatTemplate.h"

#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_MetaSoundSPLMeter"

namespace Metasound
{
	//the below stores name and tooltip information for each input/output pin.
	//so the first line stores InputAValue as "A" (name) and "Input value A." (description).
	//this is then retrieved with METASOUND_GET_PARAM_NAME_AND_METADATA.
	namespace FloatTempNodeNames
	{
		METASOUND_PARAM(InputAValue, "A", "Input value A.");
		METASOUND_PARAM(InputBValue, "B", "Input value B.");
		METASOUND_PARAM(OutputValue, "Sum of A and B", "The sum of A and B.");
	}

	FloatTempOperator::FloatTempOperator(const FOperatorSettings& InSettings,
		const FFloatReadRef& InInputValueA,
		const FFloatReadRef& InInputValueB)
		: InputA(InInputValueA),
		InputB(InInputValueB),
		FloatOutput(FFloatWriteRef::CreateNew(*InputA + *InputB)) 
	{
	
	};

	void FloatTempOperator::Execute()
	{
		*FloatOutput = *InputA + *InputB;
	}

	const FVertexInterface& FloatTempOperator::DeclareVertexInterface()
	{
		using namespace FloatTempNodeNames;

		static const FVertexInterface Interface(
			FInputVertexInterface(
				TInputDataVertexModel<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputAValue)),
				TInputDataVertexModel<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputBValue))
			),
			FOutputVertexInterface(
				TOutputDataVertexModel<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputValue))
			)
		);

		return Interface;
	};

	const FNodeClassMetadata& FloatTempOperator::GetNodeInfo()
	{
		auto CreateNodeClassMetadata = []() -> FNodeClassMetadata
			{
				FVertexInterface NodeInterface = DeclareVertexInterface();

				FNodeClassMetadata Metadata
				{
					//I get LNK errors using the StandardNodes namespace, not sure why, the variables Namespace and AudioVariant are define.
						//FNodeClassName { StandardNodes::Namespace, "Float Temp Node",
						//	 StandardNodes::AudioVariant },
						{ TEXT("UE"), TEXT("FloatTemp Node"), TEXT("Audio") },
						1, // Major Version
						0, // Minor Version
						METASOUND_LOCTEXT("FloatTempDisplayName", "Float Addition"),
						METASOUND_LOCTEXT("FloatTempNodeDesc", "A node that returns the sum of A and B"),
						PluginAuthor,
						PluginNodeMissingPrompt,
						NodeInterface,
						{ },
						{ },
						FNodeDisplayStyle{}
				};

				return Metadata;
			};

		static const FNodeClassMetadata Metadata = CreateNodeClassMetadata();
		return Metadata;
	};

	/*FDataReferenceCollection FloatTempOperator::GetInputs() const
	{
		using namespaceFloatTempNodeNames;
		FDataReferenceCollection InputDataReferences;

		InputDataReferences.AddDataReadReference(
			METASOUND_GET_PARAM_NAME(InputAValue),
			InputA);

		InputDataReferences.AddDataReadReference(
			METASOUND_GET_PARAM_NAME(InputBValue),
			InputB);

		return InputDataReferences;
	}*/
	
	/*	FDataReferenceCollection FloatTempOperator::GetOutputs() const
	{
		using namespace FloatTempNodeNames;
		FDataReferenceCollection OutputDataReferences;

		OutputDataReferences.AddDataReadReference(
			METASOUND_GET_PARAM_NAME(OutputValue),
			FloatTempOutput);

		return OutputDataReferences;
	}*/

	void FloatTempOperator::BindInputs(FInputVertexInterfaceData& InOutVertexData)
	{
		using namespace FloatTempNodeNames;
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputAValue), InputA);
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputBValue), InputB);
	}

	void FloatTempOperator::BindOutputs(FOutputVertexInterfaceData& InOutVertexData)
	{
		using namespace FloatTempNodeNames;
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputValue), FloatOutput);
	}

	TUniquePtr<IOperator> FloatTempOperator::CreateOperator(const FCreateOperatorParams& InParams, FBuildErrorArray& OutErrors)
	{
		using namespace FloatTempNodeNames;

		const Metasound::FDataReferenceCollection& InputCollection = InParams.InputDataReferences;
		const Metasound::FInputVertexInterface& InputInterface = DeclareVertexInterface().GetInputInterface();

		TDataReadReference<float> InputA = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<float>(InputInterface, METASOUND_GET_PARAM_NAME(InputAValue), InParams.OperatorSettings);
		TDataReadReference<float> InputB = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<float>(InputInterface, METASOUND_GET_PARAM_NAME(InputBValue), InParams.OperatorSettings);

		//this class is FloatTempOperator, which inherits from TExecutableOperator, which inherits from IOperator. IOperator type is returned
		return MakeUnique<FloatTempOperator>(InParams.OperatorSettings, InputA, InputB);
	}

	// Register node
	METASOUND_REGISTER_NODE(FloatTempNode);
}

#undef LOCTEXT_NAMESPACE