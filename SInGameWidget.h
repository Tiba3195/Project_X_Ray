// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class PROJECT_X_RAY_API SInGameWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInGameWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
