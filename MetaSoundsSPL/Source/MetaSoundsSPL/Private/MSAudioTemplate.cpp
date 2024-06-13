// Fill out your copyright notice in the Description page of Project Settings.


#include "MSAudioTemplate.h"

#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_MetaSoundSPLMeter"

namespace Metasound
{
	//the below stores name and tooltip information for each input/output pin.
	//so the first line stores InputAValue as "A" (name) and "Input value A." (description).
	//this is then retrieved with METASOUND_GET_PARAM_NAME_AND_METADATA.
	namespace SPLNodeNames
	{
		METASOUND_PARAM(InAudioParam, "In", "Input Audio");
		METASOUND_PARAM(OutAudioParam, "Out", "Output Audio");
	}

	FSPLOperator::FSPLOperator(const FOperatorSettings& InSettings,
		const FAudioBufferReadRef& InAudio)
		: AudioInput(InAudio),
		AudioOutput(FAudioBufferWriteRef::CreateNew(InSettings))
	{
	
	};

	void FSPLOperator::Execute()
	{
		*AudioOutput = *AudioInput;
	}

	const FVertexInterface& FSPLOperator::DeclareVertexInterface()
	{
		using namespace SPLNodeNames;

		static const FVertexInterface Interface(
			FInputVertexInterface(
				TInputDataVertexModel<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(InAudioParam))
			),
			FOutputVertexInterface(
				TOutputDataVertexModel<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutAudioParam))
			)
		);

		return Interface;
	};

	const FNodeClassMetadata& FSPLOperator::GetNodeInfo()
	{
		auto CreateNodeClassMetadata = []() -> FNodeClassMetadata
			{
				FVertexInterface NodeInterface = DeclareVertexInterface();

				FNodeClassMetadata Metadata
				{
					//I get LNK errors using the StandardNodes namespace, not sure why, the variables Namespace and AudioVariant are define.
						//FNodeClassName { StandardNodes::Namespace, "SPL Node",
						//	 StandardNodes::AudioVariant },
						{ TEXT("UE"), TEXT("SPL Node"), TEXT("Audio") },
						1, // Major Version
						0, // Minor Version
						METASOUND_LOCTEXT("SPLMeterDisplayName", "SPL Meter"),
						METASOUND_LOCTEXT("SPLMeterNodeDesc", "A node that returns the loudness of incoming sound"),
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

	/*FDataReferenceCollection FSPLOperator::GetInputs() const
	{
		using namespace SPLNodeNames;
		FDataReferenceCollection InputDataReferences;

		InputDataReferences.AddDataReadReference(
			METASOUND_GET_PARAM_NAME(InputAValue),
			InputA);

		InputDataReferences.AddDataReadReference(
			METASOUND_GET_PARAM_NAME(InputBValue),
			InputB);

		return InputDataReferences;
	}*/
	
	/*	FDataReferenceCollection FSPLOperator::GetOutputs() const
	{
		using namespace SPLNodeNames;
		FDataReferenceCollection OutputDataReferences;

		OutputDataReferences.AddDataReadReference(
			METASOUND_GET_PARAM_NAME(OutputValue),
			SPLOutput);

		return OutputDataReferences;
	}*/

	void FSPLOperator::BindInputs(FInputVertexInterfaceData& InOutVertexData)
	{
		using namespace SPLNodeNames;
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InAudioParam), AudioInput);
	}

	void FSPLOperator::BindOutputs(FOutputVertexInterfaceData& InOutVertexData)
	{
		using namespace SPLNodeNames;
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutAudioParam), AudioOutput);
	}

	TUniquePtr<IOperator> FSPLOperator::CreateOperator(const FCreateOperatorParams& InParams, FBuildErrorArray& OutErrors)
	{
		using namespace SPLNodeNames;

		const Metasound::FDataReferenceCollection& InputCollection = InParams.InputDataReferences;
		const Metasound::FInputVertexInterface& InputInterface = DeclareVertexInterface().GetInputInterface();

		FAudioBufferReadRef AudioIn = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<FAudioBuffer>(InputInterface, METASOUND_GET_PARAM_NAME(InAudioParam), InParams.OperatorSettings);

		//this class is FSPLOperator, which inherits from TExecutableOperator, which inherits from IOperator. IOperator type is returned
		return MakeUnique<FSPLOperator>(InParams.OperatorSettings, AudioIn);
	}

	// Register node
	METASOUND_REGISTER_NODE(FSPLNode);
}

#undef LOCTEXT_NAMESPACE