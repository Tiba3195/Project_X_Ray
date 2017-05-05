// Fill out your copyright notice in the Description page of Project Settings.
//All of this code is of my own creation, and I am using functions made only by Epic.

#include "Project_X_Ray.h"

#include "IngameHUD.h"
#include "GlobalGameState.h"

#define BUTTONTYPE_MAIN_RESTART 	1
#define BUTTONTYPE_MAIN_EXIT 		2

#define BUTTONTYPE_CONFIRM_YES 	1
#define BUTTONTYPE_CONFIRM_NO 	2

#define CANVAS_WHITE if(Canvas) Canvas->SetDrawColor(FColor_White);

//Cursor Draw Offset
//		use this to position texture over the point of your cursor, 
//			if the point is not at exactly 0,0
#define CURSOR_DRAW_OFFSET 3

//
//Static Consts
//
const FString AIngameHUD::S_Title_Main = FString("HUD");
const FString AIngameHUD::S_Title_Confirm = FString("Exit Game?");
const FString AIngameHUD::S_Button_Restart = FString("Restart");
const FString AIngameHUD::S_Button_Exit = FString("Exit");
const FString AIngameHUD::S_UsableInView = FString("Turret");
const FString AIngameHUD::S_TurretHardPointInView = FString("Turret Hardpoint");
const FString AIngameHUD::S_UsableInView02 = FString("Press E");
const FString AIngameHUD::S_TurretHardPointInView02 = FString("Click");
 APlayerController*	AIngameHUD::ThePC;
// Colors 
const FColor AIngameHUD::FColorBlack = FColor(0, 0, 0, 255);
const FColor AIngameHUD::FColorRed = FColor(255, 0, 0, 255);
const FColor AIngameHUD::FColorYellow = FColor(255, 255, 0, 255);
const FColor AIngameHUD::FColorBlue = FColor(0, 0, 255, 255);
const FColor AIngameHUD::FColor_White = FColor(255, 255, 255, 255);
// Backgrounds 
const FLinearColor AIngameHUD::LC_Black = FLinearColor(0, 0, 0, 1);
const FLinearColor AIngameHUD::LC_Pink = FLinearColor(1, 0, 1, 1);
const FLinearColor AIngameHUD::LC_Red = FLinearColor(1, 0, 0, 1);
const FLinearColor AIngameHUD::LC_Yellow = FLinearColor(1, 1, 0, 1);

static	bool IsFirstPerson;

//This is Really Bad, need to find a better way!
static bool DoOnce = true;

static	FVector4 CanvasDims;

static	bool IsHudInputEnabled;

static	bool UsableIsInView;

static	bool TurretHardpointIsInView;

static	bool ShowMenu;
static	bool ShowMenuWasChanged;

static FVector2D SelectionMouseLocation;
static ATurretHardPoint* CurrentSelectedHardPoint;
static ATurretActor* CurrentSelectedTurret;

INT32 InteractCounter = 0;
UDataTable* GameObjectLookupTable;
static AGlobalGameState* GS;

AIngameHUD::AIngameHUD()
{

}

AIngameHUD::AIngameHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ShowMenu = false;
	IsFirstPerson = false;
	//Draw HUD?
	DontDrawHUD = false;

	//States
	ConfirmDialogOpen = false;
	InMainMenu = true;

	//Scale
	GlobalHUDMult = 1;
	DefaultFontScale = 0.7;  

	static ConstructorHelpers::FObjectFinder<UDataTable>GameObjectLookupDataTable_BP(TEXT("DataTable'/Game/HUD/UILayout.UILayout'"));
	if (GameObjectLookupDataTable_BP.Object != nullptr )
	{
		GameObjectLookupTable = GameObjectLookupDataTable_BP.Object;
	}
	DoOnce = true;
}

void AIngameHUD::DrawCrosshair()
{
	if (FirstPersonCrosshairTexture && MotherShipCrosshairTexture)
	{
		// Find the center of our canvas.
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		if (IsFirstPerson)
		{
			// Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.
			FVector2D CrossHairDrawPosition(Center.X - (FirstPersonCrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (FirstPersonCrosshairTexture->GetSurfaceHeight() * 0.5f));

			// Draw the crosshair at the centerpoint.
			FCanvasTileItem TileItem(CrossHairDrawPosition, FirstPersonCrosshairTexture->Resource, FLinearColor::White);

			TileItem.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(TileItem);
		}
		

	//	else
	//	{
			// Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.
		//	FVector2D CrossHairDrawPosition(Center.X - (MotherShipCrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (MotherShipCrosshairTexture->GetSurfaceHeight() * 0.5f));

			// Draw the crosshair at the centerpoint.
		//	FCanvasTileItem TileItem(CrossHairDrawPosition, MotherShipCrosshairTexture->Resource, FLinearColor::White);

		//	TileItem.BlendMode = SE_BLEND_Translucent;
			//Canvas->DrawItem(TileItem);
		//}
	}
}

void AIngameHUD::SetupUIStuff()
{
	float XPos = MainMenuDims.X + 10;
	float YPos = MainMenuDims.Y + 128;

	if (GameObjectLookupTable != nullptr)
	{


	static const FString ContextString(TEXT("GENERAL"));
	TArray<FName> Narray = GameObjectLookupTable->GetRowNames();

		for (int i = 0; i < Narray.Num(); i++)	
		{
			//kinda hacky, getting a pointer to an object then making a temp value, then changing the temp and then adding the temp to the list.... should i be unloading the pointer from memory???
			FPanelStruct* GOLookupRow = GameObjectLookupTable->FindRow<FPanelStruct>(Narray[i],ContextString);
			FPanelStruct tempnewPanel = FPanelStruct();
			tempnewPanel.Dims = GOLookupRow->Dims;
			tempnewPanel.Text = GOLookupRow->Text;		
			tempnewPanel.TextOffset = GOLookupRow->TextOffset;		
			tempnewPanel.Buttons = GOLookupRow->Buttons;
		Panels.Add(tempnewPanel);
	  };	

	XPos = Canvas->SizeX / 2 - 100;
	YPos = Canvas->SizeY / 2 - 40;

	FButtonStruct newButton3 = FButtonStruct();
	newButton3.type = BUTTONTYPE_CONFIRM_YES;
	newButton3.toolTip = "";
	newButton3.Dims =FVector4(XPos, XPos + 75, YPos + 20, YPos + 60);

	//newButton3.OnPostDataImport

	//could use GetTextSize to streamline this
	XPos = Canvas->SizeX / 2 + 20;
	YPos = Canvas->SizeY / 2 - 40;
	//Add to correct array
	ButtonsConfirm.Add(newButton3);

	FButtonStruct newButton4 = FButtonStruct();
	newButton4.type = BUTTONTYPE_CONFIRM_NO;
	newButton4.toolTip = "";
	newButton3.Dims = FVector4(XPos, XPos + 75, YPos + 20, YPos + 60);

	//Add to correct array
	ButtonsConfirm.Add(newButton4);
	}
}

void AIngameHUD::DrawHUD()
{
	Super::DrawHUD();
	if (DoOnce)
	{
		SetupUIStuff();
		DoOnce = false;
	}

	//==============================
	//==============================
	//==============================
	//Have PC for Input Checks and Mouse Cursor?
	if (!ThePC)
	{
		//Attempt to Reacquire PC
		ThePC = GetOwningPlayerController();

		//Could Not Obtain PC
		if (!ThePC) return;
		//~~
	}

	//Multiplayer Safety Check
	if (!ThePC->PlayerInput) return; //not valid for first seconds of a multiplayer client
									 //~~
									 //==============================
									 //==============================
									 //==============================

		
									 //Player Input
	ThePC->GetMousePosition(MouseLocation.X, MouseLocation.Y);
	if (IsHudInputEnabled || ShowMenu)
	{
		PlayerInputChecks();
		//================
		//Get New Mouse Position
		//================

		if (ShowMenuWasChanged == true)
		{
			SetCursorMoveOnly(true);
			ShowMenuWasChanged = false;
		}
	}
	else
	{
		//this is where the menu first-> switch view-> no mouse control bug was, the problem was that i wasnt returning control to the PC after after hiding the menu in mother ship mode
		// was really cunty to find!!
		if (ShowMenuWasChanged == true)
		{
			ShowMenuWasChanged = false;
		}	
		SetCursorMoveOnly(false);
	}

	//Draw HUD?
	if (DontDrawHUD) return;
	//~~

	//Super
	Super::DrawHUD();

	//No Canvas?
	if (!Canvas) return;
	//

	//Reset States
	DrawHUD_Reset();

	DrawCommonUI();

	if (IsFirstPerson)
	{
		DrawPlayerUI();
	}
	else
	{
		DrawMothershipUI();
	}	

	DrawHUD_CheckCursorInButtons();
	//Chaeck And Show Menu
	if (ShowMenu)
	{
		//Cursor In Buttons

		//Draw Dialogs
		DrawHUD_DrawDialogs();
		//Draw Main Menu
		DrawMainMenu();
	}
	if (CurrentSelectedTurret != nullptr)
	{
		//Draw STurretUI
		DrawSelectedTurretUI();
	}
	if (CurrentSelectedHardPoint != nullptr)
	{
		//Draw SHardpoint
		DrawSelectedHardpointUI();
	}
	//Check Useable In View
	if (UsableIsInView == true)
	{
		//Usable Interact message
		IntreactMessage = S_UsableInView;
		IntreactMessagePart2 = S_UsableInView02;
	}
	//Check Hardpoint In View
	if (TurretHardpointIsInView == true)
	{
		//Hardpoint Interact message
		IntreactMessage = S_TurretHardPointInView;
		IntreactMessagePart2 = S_TurretHardPointInView02;
	}
	//TurretHardpointIsInView

	//Should be last so its the top most?
	DrawCrosshair();

	//Tool Tip
	if (ActiveButton_Tip != "") DrawToolTip();
	if (IntreactMessage != "") DrawInteractivePopup();
	
	if (IsHudInputEnabled || ShowMenu)
	{
		// Need some logic here so we know if its on or off the menu items
		DrawHUD_DrawCursor();
	}
	
}


void AIngameHUD::ToggleViewMode()
{

	if (IsFirstPerson == true)
	{
		IsFirstPerson = false;
	}
	else
	{
		IsFirstPerson = true;
	}
}

void AIngameHUD::EnableInputEX()
{
	IsHudInputEnabled = true;

}
void AIngameHUD::UsableInView()
{
	UsableIsInView = true;
}
void AIngameHUD::NoUsableInView()
{
	UsableIsInView = false;
}
void AIngameHUD::HardPointInView()
{
	TurretHardpointIsInView = true;
}
void AIngameHUD::NoHardPointInView()
{
	TurretHardpointIsInView = false;
}
// a bug here somwhere, if you show the menu and then change to first person you cant move the camera with the mouse...... needs to be fixed
void AIngameHUD::showMenu()
{
	if (ShowMenu == true)
	{
		ShowMenu = false;
		ShowMenuWasChanged = true;
	}
	else
	{
		ShowMenu = true;
		ShowMenuWasChanged = true;
	}
}
void AIngameHUD::ClearSelected()
{
	if (CurrentSelectedTurret != nullptr)
	{
		CurrentSelectedTurret = nullptr;
	}
	if (CurrentSelectedHardPoint != nullptr)
	{
		CurrentSelectedHardPoint = nullptr;
	}
}
void AIngameHUD::SetTurret(ATurretActor* turret)
{
	ThePC->GetMousePosition(SelectionMouseLocation.X, SelectionMouseLocation.Y);
	CurrentSelectedTurret = turret;
}
void AIngameHUD::SetHardPoint(ATurretHardPoint* hardpoint)
{
	ThePC->GetMousePosition(SelectionMouseLocation.X, SelectionMouseLocation.Y);
	CurrentSelectedHardPoint = hardpoint;
}
void AIngameHUD::DisableInputEX()
{
	
	IsHudInputEnabled = false;
}

//Core 

void AIngameHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Establish the PC
	ThePC = GetOwningPlayerController();

	//How to get a ref to your custom PC
	//AYourPlayerController* YourChar = Cast<AYourPlayerController>(ThePC);

	//How to Get The Character
	//AYourCharacterClass* YourChar = Cast<AYourCharacterClass>(GetOwningPawn());

}

void AIngameHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{	
		GS = Cast<AGlobalGameState>(World->GetGameState());	
		
	}
}

void AIngameHUD::DrawHUD_DrawCursor()
{
	
	//bug here, not showing hover icon on all buttons but the last one... proly has something to do with the v1 code becasue this has not changed since then!
	//Cursor Hovering in a Button?
	if (CursorHoveringInButton)
	{
		//pointer tex found?
		if (!CursorHoveringButton) return;
		DrawFullSizeTile(CursorHoveringButton, MouseLocation.X - CURSOR_DRAW_OFFSET, MouseLocation.Y - CURSOR_DRAW_OFFSET, FColor_White);
	}
	else
	{
		//cursor tex found?
		if (!CursorMain) return;
		DrawFullSizeTile(CursorMain, MouseLocation.X - CURSOR_DRAW_OFFSET, MouseLocation.Y - CURSOR_DRAW_OFFSET, FColor_White);
	}
}


//===============
// Draw Dialogs
//===============
void AIngameHUD::DrawHUD_DrawDialogs()
{

	if (ConfirmDialogOpen) DrawConfirm();
}
//Menus
void AIngameHUD::DrawMainMenu()
{

	//Draw buttons
	for (int32 p = 0; p < Panels.Num(); p++)
	{	
		FPanelStruct* Cpanel = &Panels[p];

		float XPos = Cpanel->Dims.X;
		float YPos = Cpanel->Dims.Y;

		VDrawTileMasked(PanelBackGround, XPos, YPos, Cpanel->Dims.Z, Cpanel->Dims.W, FColor(255, 255, 255, 120)); //alpha 120/255

		// check if count >0 because of a bug i wrote(justin)	
		if (Cpanel->Buttons.Num() > 0)
		{
			for (int32 b = 0; b < Cpanel->Buttons.Num(); b++)
			{			
				DrawMainMenuButtons(&Cpanel->Buttons[b]);			
			}
	    }			
	}	
}
void AIngameHUD::DrawConfirm()
{
	//Blue rect with alpha 50%
	VDrawTile(DialognBackground, Canvas->SizeX / 2 - 100, Canvas->SizeY / 2 - 50, 200, 100,FColor(255, 255, 255, 120)); //alpha 120/255
	
	//Draw buttons
	DrawConfirmButtons();
}

//Buttons
void AIngameHUD::DrawMainMenuButtons(FButtonStruct* button)
{
	//Start Point
	float XPos = button->Dims.X;
	float YPos = button->Dims.Y;
	FVector2D BCenter = FVector2D(XPos + button->Dims.Z / 4, YPos + button->Dims.W / 4);

	//check cursor in bounds
	if (button->Dims.X <= MouseLocation.X && MouseLocation.X <= button->Dims.X + button->Dims.Z &&
		button->Dims.Y <= MouseLocation.Y && MouseLocation.Y <= button->Dims.Y + button->Dims.W)
	{
		//Active Button Type
	//	ActiveButton_Type = CurCheckButton->type;
		//Tool Tip
		ActiveButton_Tip = button->toolTip;
		//Change Cursor
		CursorHoveringInButton = true;

		if (ThePC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			if (CurrentSelectedHardPoint != nullptr)
			{
				GS->SetCurrentHardPointIndex(CurrentSelectedHardPoint->HardPointIndex);
			}
			// check if not = "" because of a bug i wrote
			if (button->Command != "")
			{				
			   ThePC->ConsoleCommand(button->Command);
			}
		}
	}
	else
	{
		CursorHoveringInButton = false;
	}
		//Background

		if (CursorHoveringInButton)
		{
			VDrawTileMasked(ButtonHoverBackground, XPos, YPos, button->Dims.Z, button->Dims.W, FColor(255, 255, 255, 120)); //alpha 120/255
																							  //Cursor Hovering in a Button?
		}
		else
		{
			VDrawTileMasked(ButtonBackground, XPos, YPos, button->Dims.Z, button->Dims.W, FColor(255, 255, 255, 120)); //alpha 120/255
																							  //Cursor Hovering in a Button?
		}
																						  //Text
		DrawJoyText(
			VerdanaFont, button->Text, BCenter.X + button->TextOffset.X, BCenter.Y + button->TextOffset.Y,
			FColor_White, 2,
			true, FColor_White
		);	
	
}
void AIngameHUD::DrawConfirmButtons()
{
	float xStart = Canvas->SizeX / 2 - 100;
	float yStart = Canvas->SizeY / 2 - 40;
	//DialognBackground
	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_YES) ColorPtr = &LC_Pink;
	else ColorPtr = &LC_Yellow;

	//Text
	DrawJoyText(
		VerdanaFont, "Yes", xStart + 30, yStart + 20,
		*ColorPtr, 2,
		true
	);

	xStart = Canvas->SizeX / 2 + 20;
	yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_NO) ColorPtr = &LC_Black;
	else ColorPtr = &LC_Yellow;

	//Text
	DrawJoyText(
		VerdanaFont, "No", xStart + 30, yStart + 20,
		*ColorPtr, 2,
		true
	);
}

//===============
// Cursor In Buttons
//===============
int32 AIngameHUD::CheckCursorInButton(const TArray<FButtonStruct>& ButtonArray)
{
	for (int32 b = 0; b < ButtonArray.Num(); b++)
	{
		CurCheckButton = &ButtonArray[b];
		bool istrue = true;
	
		//check cursor in bounds
		if (CurCheckButton->Dims.X <= MouseLocation.X && MouseLocation.X <= CurCheckButton->Dims.Z &&
			CurCheckButton->Dims.Y <= MouseLocation.Y && MouseLocation.Y <= CurCheckButton->Dims.W)
		{

			//Active Button Type
			ActiveButton_Type = CurCheckButton->type;

			//Tool Tip
			ActiveButton_Tip = CurCheckButton->toolTip;

			//Change Cursor
			CursorHoveringInButton = true;

			//Mouse Clicked?
			if (ThePC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
			{
				// check if not = "" because of a bug i wrote
				if (CurCheckButton->Command !="")
				{
					ThePC->ConsoleCommand(CurCheckButton->Command);
			    }
				return ActiveButton_Type;
				//~~
				//no need to check rest of buttons
			}			
		}
		else
		{
		}
	}

	//No Click Occurred This Tick
	return -1;
}

//Check Confirm
void AIngameHUD::CheckCursorInButtonsConfirm()
{
	//Check Confirm Buttons
	ClickedButtonType = CheckCursorInButton(ButtonsConfirm); //fills global ActiveButton_Type

	if (ClickedButtonType == BUTTONTYPE_CONFIRM_YES)
	{
		ThePC->ConsoleCommand("Exit");
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_CONFIRM_NO)
	{
		ConfirmDialogOpen = false;
		ButtonsConfirm.Empty(); //Buttons not needed anymore
		return;
	}
}

//Check Buttons
void AIngameHUD::CheckCursorInButtonsMain()
{
	//Check Confirm Buttons
	//ClickedButtonType = CheckCursorInButton(MainMenuButtons);

	//if (ClickedButtonType == BUTTONTYPE_MAIN_RESTART)
	//{
	//	ThePC->ConsoleCommand("RestartLevel");
	//	return;
	//}
	//if (ClickedButtonType == BUTTONTYPE_MAIN_EXIT)
	//{
	//	ConfirmDialogOpen = true;
	//	return;
	//}
}
void AIngameHUD::DrawHUD_CheckCursorInButtons()
{
	if (ConfirmDialogOpen)
	{
		CheckCursorInButtonsConfirm();

		//Take Focus Away From All Other buttons
		return;
		//~
	}

	//Main
	CheckCursorInButtonsMain();
}

void AIngameHUD::DrawToolTip()
{
	//if mouse is too far to right, draw from left instead
	float xStart = MouseLocation.X + 150;
	float yStart = MouseLocation.Y + 5;

	//out vars
	float RV_xLength;
	float RV_yLength;
	//Text Size
	GetTextSize(
		ActiveButton_Tip,
		RV_xLength,
		RV_yLength,
		UE4Font,
		DefaultFontScale * 2
	);

	// Decide Draw to Left or to the Right 

	//Draw to the Left
	if (xStart + RV_xLength >= Canvas->SizeX - 40)
	{
		xStart -= 150 + 140 + 64 + RV_xLength;

		//If Text is too long, bring it closer to the cursor
		if (xStart < 33) xStart = 33;
	}

	//Background
	VDrawTile(LightWindowBackground, xStart, yStart,
		RV_xLength + 70,
		80, FColor(255, 255, 255, 120)); //alpha 120/255	

	//Tool Tip
	DrawText(
		ActiveButton_Tip,
		LC_Pink,
		xStart + 32, yStart + 20,
		UE4Font,
		DefaultFontScale * 2,
		false		//scale position of message with HUD scale
	);
}

void AIngameHUD::DrawInteractivePopup()
{
	// Find the center of our canvas.
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);




	if (IsFirstPerson)
	{
		//Tool Tip IntreactMessagePart2
		DrawText(
			IntreactMessage,
			LC_Red,
			Center.X - 75, Center.Y,
			UE4Font,
			DefaultFontScale *2,
			false		//scale position of message with HUD scale
		);
		DrawText(
			IntreactMessagePart2,
			LC_Red,
			Center.X - 75, Center.Y +35,
			UE4Font,
			DefaultFontScale * 2,
			false		//scale position of message with HUD scale
		);
	}
	else
	{
		//Tool Tip
		DrawText(
			IntreactMessage,
			LC_Red,
			MouseLocation.X + 25, MouseLocation.Y,
			UE4Font,
			DefaultFontScale * 2,
			false		//scale position of message with HUD scale
		);
		DrawText(
			IntreactMessagePart2,
			LC_Red,
			MouseLocation.X + 25, MouseLocation.Y +35,
			UE4Font,
			DefaultFontScale * 2,
			false		//scale position of message with HUD scale
		);
	}	
}

void AIngameHUD::DrawCommonUI()
{
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	VDrawTile(MiniMapFrame, Center.X + MiniMapDims.X, Center.Y + MiniMapDims.Y, MiniMapDims.Z, MiniMapDims.W, FColor(255, 255, 255, 120)); //alpha 120/255
}

void AIngameHUD::DrawPlayerUI()
{
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	/** Player UI */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
	//	UTexture2D* PlayerHelthBarBG;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
	//	UTexture2D* PlayerHelthBarFG;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
	//	UTexture2D* PlayerStaminarBG;
//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
	//	UTexture2D* PlayerStaminaFG;


	//Background
	VDrawTileMasked(PlayerHelthBarBG, Center.X + PlayerHelthBarDims.X, Center.Y + PlayerHelthBarDims.Y, PlayerHelthBarDims.Z, PlayerHelthBarDims.W, FColor(255, 255, 255, 120)); //alpha 120/255
    //Forground
	VDrawTileMasked(PlayerHelthBarFG, Center.X + PlayerHelthBarDims.X, Center.Y + PlayerHelthBarDims.Y, PlayerHelthBarDims.Z, PlayerHelthBarDims.W, FColor(255, 255, 255, 255)); //alpha 120/255

    //Background
	VDrawTileMasked(PlayerStaminarBG, Center.X + PlayerStaminarDims.X, Center.Y + PlayerStaminarDims.Y, PlayerStaminarDims.Z, PlayerStaminarDims.W, FColor(255, 255, 255, 120)); //alpha 120/255
	//Forground
	VDrawTileMasked(PlayerStaminaFG, Center.X + PlayerStaminarDims.X, Center.Y + PlayerStaminarDims.Y, PlayerStaminarDims.Z, PlayerStaminarDims.W, FColor(255, 255, 255, 255)); //alpha 120/255
																					  //Text
//	DrawJoyText(
	//	VerdanaFont, "Restart", Center.X + 30, Center.Y + 20,
	//	LC_Black, DefaultFontScale,
	//	true, LC_Red
	//);

	//Struct
	//Add Button If Necessary
	//		could be cleared and need refreshing if using a different menu
	//			clear buttons with ButtonsMain.Empty()
	//if (ButtonsMain.Num() < 1)
	//{
	//	FJoyButtonStruct newButton = FJoyButtonStruct();
	//	newButton.type = BUTTONTYPE_MAIN_RESTART;
	//	newButton.toolTip = "Restart the Game!";
	//	newButton.minX = Center.X;
	//	newButton.maxX = Center.X + 150;
	//	newButton.minY = Center.Y;
	//	newButton.maxY = Center.Y + 80;

		//Add to correct array
	//	ButtonsMain.Add(newButton);
	//}


	Center.X = 100;
	Center.Y = 410;
}

void AIngameHUD::DrawMothershipUI()
{
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	VDrawTile(MotherShipTopBar, Center.X + MotherShipTopBarDims.X, Center.Y + MotherShipTopBarDims.Y, MotherShipTopBarDims.Z, MotherShipTopBarDims.W, FColor(255, 255, 255, 120)); //alpha 120/255

}

void AIngameHUD::DrawSelectedTurretUI()
{
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	VDrawTile(STurretMenuBG, Center.X + STurretMenuBGDim.X, Center.Y + STurretMenuBGDim.Y, STurretMenuBGDim.Z, STurretMenuBGDim.W, FColor(255, 255, 255, 120)); //alpha 120/255
}

void AIngameHUD::DrawSelectedHardpointUI()
{
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	VDrawTile(SHardpointMenuBG, Center.X + SHardpointMenuBGDim.X, Center.Y + SHardpointMenuBGDim.Y, SHardpointMenuBGDim.Z, SHardpointMenuBGDim.W, FColor(255, 255, 255, 120)); //alpha 120/255
}


void AIngameHUD::PlayerInputChecks()
{
	//check out this tutorial of mine for a list of all EKeys::
	//http://forums.epicgames.com/threads/972861-Tutorials-C-for-UE4-Code-Samples-gt-gt-New-Video-Freeze-Render-When-Tabbed-Out?p=31660286&viewfull=1#post31660286

	if (ThePC->WasInputKeyJustPressed(EKeys::Escape))
	{
		SetCursorMoveOnly(false);
		return;
	}
	if (ThePC->WasInputKeyJustPressed(EKeys::F))
	{
		SetCursorMoveOnly(!ThePC->IsLookInputIgnored());
		return;
	}
	if (ThePC->WasInputKeyJustPressed(EKeys::H))
	{
		DontDrawHUD = !DontDrawHUD;
		return;
	}

	//Confirm
	if (ConfirmDialogOpen)
	{
		if (ThePC->WasInputKeyJustPressed(EKeys::Y))
		{
			ThePC->ConsoleCommand("Exit");
			//could replace with function based on confirm context

			return;
		}
		if (ThePC->WasInputKeyJustPressed(EKeys::N))
		{
			ConfirmDialogOpen = false;
			ButtonsConfirm.Empty(); //Buttons not needed anymore
									//Cancel Confirm

			return;
		}
	}
}

void AIngameHUD::SetupMainMenu()
{
}

void AIngameHUD::DrawHUD_Reset()
{
	ActiveButton_Type = -1;
	ActiveButton_Tip = "";
	IntreactMessage = "";
	IntreactMessagePart2 = "";
	CursorHoveringInButton = false;
}


