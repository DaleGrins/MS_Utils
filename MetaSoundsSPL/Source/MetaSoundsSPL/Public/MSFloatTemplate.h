// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MetasoundExecutableOperator.h"
#include "Internationalization/Text.h"
#include "MetasoundPrimitives.h"
#include "MetasoundTime.h"
#include "MetasoundNodeRegistrationMacro.h"
#include "MetasoundStandardNodesNames.h" 
#include "MetasoundFacade.h"
#include "MetasoundParamHelper.h" 

	//------------------------------------------------------------------------------------
	// FloatTempOperator
	//------------------------------------------------------------------------------------

namespace Metasound
{
	class FloatTempOperator : public TExecutableOperator<FloatTempOperator>
	{
	public:
		FloatTempOperator(const FOperatorSettings& InSettings, const FFloatReadRef& InInputValueA, const FFloatReadRef& InInputValueB);

		//UFUNCTION()
		//static functions exist across the class and not instances. They cannot access member instance variables or non-static members
		//they can only access other static members (variables or methods) of the class.
		static const FVertexInterface& DeclareVertexInterface();

		//UFUNCTION()
		static const FNodeClassMetadata& GetNodeInfo();

		//UFUNCTION
		//virtual FDataReferenceCollection GetInputs() const override;

		//UFUNCTION
		//virtual FDataReferenceCollection GetOutputs() const override;

		virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override;
		virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override;

		//UFUNCTION
		// Used to instantiate a new runtime instance of your node
		static TUniquePtr<IOperator> CreateOperator(const FCreateOperatorParams& InParams, FBuildErrorArray& OutErrors);

		//UFUNCTION()
		void Execute();

	private:

		FFloatReadRef InputA;
		FFloatReadRef InputB;

		FFloatWriteRef FloatOutput;
	};

	//------------------------------------------------------------------------------------
	// FloatTempNode
	//------------------------------------------------------------------------------------

	// Node Class - Inheriting from FNodeFacade is recommended for nodes that have a static FVertexInterface
	class FloatTempNode : public FNodeFacade
	{
	public:
		FloatTempNode(const FNodeInitData& InitData) : FNodeFacade(InitData.InstanceName, InitData.InstanceID,
			TFacadeOperatorClass<FloatTempOperator>())
		{
		}
	};

}


