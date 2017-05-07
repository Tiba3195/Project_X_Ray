// Fill out your copyright notice in the Description page of Project Settings.
// All of this code is of my own creation, and I am using functions made only by Epic.
#pragma once

#include "GameFramework/HUD.h"
#include "TurretActor.h"
#include "TurretHardPoint.h"
#include "IngameHUD.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FButtonStruct : public FTableRowBase
{
	GENERATED_BODY()
public:
		//Vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	INT32 		type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString	toolTip;
	//Pos: X Y, Size: W H
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector4 Dims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TextOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TextSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Command;
	//~

	//default properties

	FButtonStruct()
	{
		type = -1;
		toolTip = "";
		Text = "";
		Command = "";
		Dims = FVector4(0.0f,0.0f,0.0f,0.0f);	
		TextOffset = FVector2D(0.0f, 0.0f);
		TextSize = FVector2D(0.0f, 0.0f);
	}
	
};
USTRUCT(BlueprintType)
struct FPanelStruct : public FTableRowBase
{
	GENERATED_BODY()
public:
	//Vars
	//Pos: X Y, Size: W H
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector4 Dims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D TextOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D TextSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FButtonStruct> Buttons;
	//~

	//default properties

	FPanelStruct()
	{

		Text = "";
		Dims = FVector4(0.0f, 0.0f, 0.0f, 0.0f);
		TextOffset = FVector2D(0.0f, 0.0f);
		TextSize = FVector2D(0.0f, 0.0f);
		//Buttons = TArray< FButtonStruct >;
	}

};


UCLASS()
class PROJECT_X_RAY_API AIngameHUD : public AHUD
{
	GENERATED_BODY()




public:
	AIngameHUD();
	AIngameHUD(const FObjectInitializer& ObjectInitializer);	

	
protected:


	// This will be drawn at the center of the screen.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* FirstPersonCrosshairTexture;
	// This will be drawn at the center of the screen.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* MotherShipCrosshairTexture;

	/** Verdana */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UFont* VerdanaFont;

	/** Put Roboto Here */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UFont* UE4Font;

	/** Font Scaling Used By Your HUD Code */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		float DefaultFontScale;

	/** HUD Scaling */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Menu")
		float GlobalHUDMult;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Menu")
		FVector4 ExitButtonDims = FVector4(0.0f, 0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Menu")
		FVector4 ResetButtonDims = FVector4(0.0f, 0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Menu")
		FVector4 MainMenuDims = FVector4(0.0f, 0.0f, 0.0f, 0.0f);

	// T2D 
	/** Cursor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* CursorMain;

	/** Hovering */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* CursorHoveringButton;

	/** Button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* ButtonBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* ButtonHoverBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* PanelBackGround;

	/** Dialog */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* DialognBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* DarkWindowBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* LightWindowBackground;

	/** Common UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* MiniMapFrame;
	//Sets the Camera Offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		FVector4 MiniMapDims = FVector4(0.0f, 0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* STurretMenuBG;
	//Sets the Camera Offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		FVector4 STurretMenuBGDim = FVector4(0.0f, 0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		UTexture2D* SHardpointMenuBG;
	//Sets the Camera Offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common UI")
		FVector4 SHardpointMenuBGDim = FVector4(0.0f, 0.0f, 0.0f, 0.0f);

	/** Mothership UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mothership UI")
		UTexture2D* MotherShipTopBar;
	//Sets the Camera Offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mothership UI")
		FVector4 MotherShipTopBarDims = FVector4(0.0f, 0.0f, 0.0f, 0.0f);
	/** Player UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player UI")
		UTexture2D* PlayerHelthBarBG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player UI")
		UTexture2D* PlayerHelthBarFG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player UI")
		UTexture2D* PlayerStaminarBG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player UI")
		UTexture2D* PlayerStaminaFG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player UI")
		FVector4 PlayerHelthBarDims = FVector4(0.0f, 0.0f, 0.0f,0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player UI")
		FVector4 PlayerStaminarDims = FVector4(0.0f, 0.0f, 0.0f, 0.0f);

	// Materials 
	/** Events */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
		UMaterialInterface* MaterialBackground;

	//

	/* Draw Hud? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)
		bool DontDrawHUD;

	 void DrawCrosshair();

	 void SetupUIStuff();

	 //Draw HUD
	 void DrawHUD_Reset();
	 /** after all game elements are created */
	 virtual void PostInitializeComponents() override;


public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void DrawHUD_DrawCursor();
	// Primary draw call for the HUD.
	virtual void DrawHUD() override;

	static void ToggleViewMode();

	static void DisableInputEX();
	static void EnableInputEX();
	static void UsableInView();
	static void NoUsableInView();
	static void HardPointInView();
	static void NoHardPointInView();
	static void showMenu();
	static void ClearSelected();

	static void SetTurret(ATurretActor* turret);

	static void SetHardPoint(ATurretHardPoint* hardpoint);

	FVector2D MouseLocation;	


	//Buttons


	TArray<FPanelStruct> Panels;
	TArray<FButtonStruct> ButtonsConfirm;

	//Cursor In buttons
	void DrawHUD_CheckCursorInButtons();
	void CheckCursorInButtonsMain();
	void CheckCursorInButtonsConfirm();

	const FButtonStruct* CurCheckButton;
	int32 CheckCursorInButton(const TArray<FButtonStruct>& ButtonArray);
	int32 ClickedButtonType;
	//States
	bool ConfirmDialogOpen;
	bool InMainMenu;

	int32 		ActiveButton_Type;
	FString 	ActiveButton_Tip;
	FString 	IntreactMessage;
	FString 	IntreactMessagePart2;
	
	bool CursorHoveringInButton;
	//Colors

	const FLinearColor * ColorPtr;

	//Colors
	static const FColor		FColorBlack;
	static const FColor		FColorRed;
	static const FColor		FColorYellow;
	static const FColor		FColorBlue;
	static const FColor		FColor_White;

	static const FLinearColor LC_Black;
	static const FLinearColor LC_Pink;
	static const FLinearColor LC_Red;
	static const FLinearColor LC_Yellow;
	//FString


	//`Titles
	static const FString S_Title_Main;
	static const FString S_Title_Confirm;
	//`Button Text
	static const FString S_Button_Restart;
	static const FString S_Button_Exit;

	static const FString S_UsableInView;
	static const FString S_UsableInView02;
	static const FString S_TurretHardPointInView;
	static const FString S_TurretHardPointInView02;
	// Utility 

	//Stop Camera From Moving With Mouse
	FORCEINLINE void SetCursorMoveOnly(bool CursorOnly)
	{
		if (!ThePC) return;
		//
		ThePC->SetIgnoreLookInput(CursorOnly);

	}

	//DrawLine
	FORCEINLINE void DrawJoyLine
	(
		const FVector2D& Start,
		const FVector2D& End,
		const FLinearColor& TheColor,
		const float& Thick
	)
	{
		if (!Canvas) return;
		//

		FCanvasLineItem NewLine(Start, End);
		NewLine.SetColor(TheColor);
		NewLine.LineThickness = Thick;
		Canvas->DrawItem(NewLine);
	}

	//~

	FORCEINLINE void DrawJoyRect(
		float X, float Y,
		float Width, float Height,
		const FLinearColor& Color
	)
	{
		if (!Canvas) return;
		//

		FCanvasTileItem RectItem(
			FVector2D(X, Y),
			FVector2D(Width, Height),
			Color
		);

		RectItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(RectItem);
	}

	//~

	//DrawText
	FORCEINLINE void DrawJoyText(
		UFont*	TheFont,
		const FString& TheStr,
		const float& X, const float& Y,
		const FLinearColor& TheColor,
		const float& TheScale,
		bool DrawOutline = false,
		const FLinearColor OutlineColor = FLinearColor(0, 0, 0, 1)
	) {
		if (!Canvas) return;
		//

		//Text and Font
		FCanvasTextItem NewText(
			FVector2D(X, Y),
			FText::FromString(TheStr),
			TheFont,
			TheColor
		);

		//Text Scale
		NewText.Scale.Set(TheScale, TheScale);

		//Outline gets its alpha from the main color
		NewText.bOutlined = true;
		NewText.OutlineColor = OutlineColor;
		NewText.OutlineColor.A = TheColor.A * 2;

		//Draw
		Canvas->DrawItem(NewText);
	}

	//~
	//Draw Full Size Tile
	FORCEINLINE void DrawFullSizeTile(UTexture2D* tex, float x, float y, const FColor& Color)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~~

		Canvas->SetDrawColor(Color);

		//Draw
		Canvas->DrawTile(
			tex, x, y, 
			tex->GetSurfaceWidth(), //screen width
			tex->GetSurfaceHeight(),  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_Translucent
		);
	}

	//~

	FORCEINLINE void VDrawTile(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~

		Canvas->SetDrawColor(TheColor);

		//Draw
		Canvas->DrawTile(
			tex, x, y,
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_Translucent
		);
	}
	//enum EBlendMode
	//{
	//	BLEND_Opaque = 0,
	//	BLEND_Masked = 1,
	//	BLEND_Translucent = 2,
		//BLEND_Additive = 3,
		//BLEND_Modulate = 4,
	//	BLEND_AlphaComposite = 5,
		//BLEND_MAX = 6,
//	};

	FORCEINLINE void VDrawTileAlphaComposite(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~

		Canvas->SetDrawColor(TheColor);

		//Draw
		Canvas->DrawTile(
			tex, x, y,
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_AlphaComposite
		);
	}
	FORCEINLINE void VDrawTileMasked(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~

		Canvas->SetDrawColor(TheColor);

		//Draw
		Canvas->DrawTile(
			tex, x, y,
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_Masked
		);
	}
	FORCEINLINE void VDrawTileAlpha(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~

		Canvas->SetDrawColor(TheColor);

		//Draw
		Canvas->DrawTile(
			tex, x, y,
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_Translucent
		);
	}
	FORCEINLINE void VDrawTileOpaque(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~

		Canvas->SetDrawColor(TheColor);

		//Draw
		Canvas->DrawTile(
			tex, x, y,
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_Opaque
		);
	}
	FORCEINLINE void VDrawTileAdditive(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~

		Canvas->SetDrawColor(TheColor);

		//Draw
		Canvas->DrawTile(
			tex, x, y,
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_Additive
		);
	}
	FORCEINLINE void VDrawTileModulate(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~

		Canvas->SetDrawColor(TheColor);

		//Draw
		Canvas->DrawTile(
			tex, x, y,
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_Modulate
		);
	}
	FORCEINLINE void VDrawTileMAX(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~

		Canvas->SetDrawColor(TheColor);

		//Draw
		Canvas->DrawTile(
			tex, x, y,
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_MAX
		);
	}
	//~

	//Draw

	void DrawHUD_DrawDialogs();

	//Menus
	void DrawMainMenu();
	void DrawConfirm();

	//Buttons
	void DrawMainMenuButtons(FButtonStruct* button);
	void DrawConfirmButtons();

	void DrawToolTip();
	void DrawInteractivePopup();

	void DrawCommonUI();
	void DrawPlayerUI();
	void DrawMothershipUI();

	void DrawSelectedTurretUI();
	void DrawSelectedHardpointUI();

 static	APlayerController* ThePC;

	void PlayerInputChecks();
	void SetupMainMenu();

	//bool CallFunctionByNameWithArguments(const TCHAR* Str,  UObject* Executor);
};
