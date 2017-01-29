#include "../../Headers/Engine/Editor.h"
#include "../../Headers/UI/Theme.h"
#include "../../Headers/UI/UICreationMacros.h"

namespace Engine
{

  Editor::Editor()
  {
    EditorFont.loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");
    EditorModeText.setFont(EditorFont);
    EditorModeText.setCharacterSize(8);
    EditorModeText.setFillColor(sf::Color::White);
    EditorModeText.setPosition({ 400, 10 });
    EditorModeText.setString("Editor : Mode <No Selection>");

    MenuFont = std::make_shared<sf::Font>();
    MenuFont->loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Marvel-Regular.ttf");

    TextFont = std::make_shared<sf::Font>();
    TextFont->loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");

    PreviewGridInfoText.setFont(EditorFont);
    PreviewGridInfoText.setCharacterSize(6);
    PreviewGridInfoText.setFillColor(sf::Color::White);
    PreviewGridInfoText.setPosition({ 10, 820 });
    PreviewGridInfoText.setString("Grid Cell: 40 x 40");

    //create the grid lines for the preview
    sf::Vector2f GridStart = { 0, 40 };
    sf::Vector2f GridCellSize = { 40.f, 40.f };
    sf::Vector2f Pos1, Pos2, Pos3, Pos4;

    //set info for tile editing
    TileEditInfo.TileText.setFont(EditorFont);
    TileEditInfo.TileSheet.loadFromFile("./SFEngine/Samples/Levels/Graveyard/TileSheetGraveyard.png");

    TileEditInfo.TileSheetSprite.setTexture(TileEditInfo.TileSheet);
    TileEditInfo.TileSheetPreviewSprite.setTexture(TileEditInfo.TileSheet);

    //get factors needed for scaling sprites (so they fit inside their boundaries)
    sf::Vector2f ScaleFactors = sf::Vector2f({
      400.f / TileEditInfo.TileSheet.getSize().x, 400.f / TileEditInfo.TileSheet.getSize().y
    });

    TileEditInfo.TileSheetSprite.setPosition({ TileSheetPreviewPosition });
    TileEditInfo.TileSheetSprite.setScale(ScaleFactors);

    UITexture = std::shared_ptr<sf::RenderTexture>(new sf::RenderTexture);
    UITexture->create(1200, 900);
    UISprite.setTexture(UITexture->getTexture());

    TilesTexture = std::make_shared<sf::Texture>();
    TilesTexture->loadFromFile("./SFEngine/Samples/Levels/Graveyard/TileSheetGraveyard.png");

    try
    {
      UIHelper = UI::WidgetHelper::Create();
      UILayer = UI::UILayer::Create(UIHelper);
      UIHelper->AddUILayer(UILayer);

      TestButton = UI::ClickButtonBase::Create(UILayer, UIHelper, { 800, 600 }, { 150, 45 });
      TestButton2 = UI::ClickButtonBase::Create(UILayer, UIHelper, { 400, 800 }, { 150, 45 });

      TestButton->ButtonText.setFont(EditorFont);
      TestButton->ButtonText.setCharacterSize(16);
      TestButton->ButtonText.setString("TestButton");
      TestButton->ButtonText.setFillColor(sf::Color::White);
      TestButton->ButtonText.setPosition({ 820, 820 });

      float ScaleX = 400.f / TilesTexture->getSize().x;
      float ScaleY = 400.f / TilesTexture->getSize().y;

      sf::Vector2f TileStart{ 810, 40 };
      sf::IntRect LastTileDim{ 0,0,0,0 };
      sf::FloatRect ThisTileDim;
      for (auto & tile : TileFrames) {
        ThisTileDim.left = TileStart.x + ScaleX * tile.left;
        ThisTileDim.top = TileStart.y + ScaleY * tile.top;
        ThisTileDim.width = tile.width;
        ThisTileDim.height = tile.height;

        try {
          auto _tile = UI::DraggableTile::Create(UILayer, UIHelper, TilesTexture, tile, { ThisTileDim.left, ThisTileDim.top }, { ThisTileDim.width * ScaleX, ThisTileDim.height * ScaleY });
          DragTiles.push_back(_tile);
        }
        catch (ConstructionException &cerr) {
          std::cerr << "Draggable exception error:\n" << cerr.what() << std::endl;
        }
      } //for tile : TileFrames


      //EditOptionsList = UI::ListWidget::Create(UILayer, UIHelper, TextFont, { 0, 0 }, { 1200.f, 80.f },
      //                                         UI::ButtonPlacement::BottomCenter, { 0.f, 15.f }, { 100.f, 15.f });

      //TestPopup = UI::PopupObject::Create(UILayer, UIHelper, { 100, 100 }, { 900, 700 }, TextFont);

      sf::Vector2f ObjectSelectMenuPosition = { 100, 100 };
      sf::Vector2f ObjectSelectMenuSize = { 200, 400 };
      sf::Vector2f ObjectSelectMenuScreenPosition = { 100, 100 };
      sf::Vector2f ObjectSelectMenuScreenSize = { 200, 400 };

      //ObjectSelectMenu = UI::MenuWidget::Create(UILayer, UIHelper, { 100, 100 }, { 200, 400 });
      MakeMenu(ObjectSelectMenu, UILayer, UIHelper);
      MakeMenuDefaultScreen(ObjectSelectTypeScreen, UI::DefaultDarkTheme, ObjectSelectMenu);
      MakeMenuScreen(ObjectSelectPhysicsObjectScreen, UI::DefaultDarkTheme, ObjectSelectMenu);
      MakeMenuScreen(ObjectSelectLightObjectScreen, UI::DefaultDarkTheme, ObjectSelectMenu);
      MakeMenuScreen(ObjectSelectEffectObjectScreen, UI::DefaultDarkTheme, ObjectSelectMenu);

      AddMenuScreen(ObjectSelectMenu, ObjectSelectPhysicsObjectScreen);
      AddMenuScreen(ObjectSelectMenu, ObjectSelectLightObjectScreen);
      AddMenuScreen(ObjectSelectMenu, ObjectSelectEffectObjectScreen);

      //Make buttons and transitions on first menu screen
      MakeMenuScreenButtonNormal(ObjectSelectType_PhysicsObjectButton, ObjectSelectTypeScreen, ObjectSelectMenu, sf::Vector2f(150, 110), UI::DefaultDarkTheme, "Physics Object", MenuFont);
      MakeMenuScreenTransition(ObjectSelectType_PhysicsObjectButton, ObjectSelectMenu, ObjectSelectPhysicsObjectScreen);

      MakeMenuScreenButtonNormal(ObjectSelectType_LightObjectButton, ObjectSelectTypeScreen, ObjectSelectMenu, sf::Vector2f(150, 160), UI::DefaultDarkTheme, "Light Object", MenuFont);
      MakeMenuScreenTransition(ObjectSelectType_LightObjectButton, ObjectSelectMenu, ObjectSelectLightObjectScreen);

      MakeMenuScreenButtonNormal(ObjectSelectType_EffectObjectButton, ObjectSelectTypeScreen, ObjectSelectMenu, sf::Vector2f(150, 210), UI::DefaultDarkTheme, "Effect Object", MenuFont);
      MakeMenuScreenTransition(ObjectSelectType_EffectObjectButton, ObjectSelectMenu, ObjectSelectEffectObjectScreen);

      MakeMenuScreenButtonNormal(ObjectSelectType_CancelButton, ObjectSelectTypeScreen, ObjectSelectMenu, sf::Vector2f(150, 260), UI::DefaultDarkTheme, "Cancel", MenuFont);
      MakeMenuButtonClose(ObjectSelectType_CancelButton, ObjectSelectMenu);

      //Make buttons and transitions on the second screen
      MakeMenuScreenButtonNormal(ObjectSelect_BallButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(150, 110), UI::DefaultDarkTheme, "Ball", MenuFont);
      MakeMenuButtonClose(ObjectSelect_BallButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_SquareButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(150, 160), UI::DefaultDarkTheme, "Square", MenuFont);
      MakeMenuButtonClose(ObjectSelect_SquareButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_RectButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(150, 210), UI::DefaultDarkTheme, "Rectangle", MenuFont);
      MakeMenuButtonClose(ObjectSelect_RectButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_TriangleButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(150, 260), UI::DefaultDarkTheme, "Triangle", MenuFont);
      MakeMenuButtonClose(ObjectSelect_TriangleButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_5PolyButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(150, 310), UI::DefaultDarkTheme, "5Poly", MenuFont);
      MakeMenuButtonClose(ObjectSelect_5PolyButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_BackToSelectTypeButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(150, 360), UI::DefaultDarkTheme, "Change Type", MenuFont);
      MakeMenuScreenButtonBack(ObjectSelect_BackToSelectTypeButton, ObjectSelectPhysicsObjectScreen);

      //Light object menu screen
      MakeMenuScreenButtonNormal(LightSelect_CancelButton, ObjectSelectLightObjectScreen, ObjectSelectMenu, sf::Vector2f(150, 110), UI::DefaultDarkTheme, "Back", MenuFont);
      MakeMenuScreenButtonBack(LightSelect_CancelButton, ObjectSelectLightObjectScreen);

      //Effect object menu screen
      MakeMenuScreenButtonNormal(EffectSelect_CancelButton, ObjectSelectEffectObjectScreen, ObjectSelectMenu, sf::Vector2f(150, 110), UI::DefaultDarkTheme, "Back", MenuFont);
      MakeMenuScreenButtonBack(EffectSelect_CancelButton, ObjectSelectEffectObjectScreen);

      //SelectPhysicsObject Screen

      MakeButtonNormal(AllObjectButton, UILayer, UIHelper, sf::Vector2f(10, 10), sf::Vector2f(150, 40), UI::DefaultDarkTheme);
      auto label = UI::TextLabel::Create(AllObjectButton, UIHelper, UI::TextAlignment::CenterJustified, "Add Object", sf::Color(0, 129, 155), MenuFont, 14, { 0,0,1000,1000 }, { 0,0 });
      AllObjectButton->MousePressCB = [this]() 
      {
        //open the object select menu
        UI::MenuWidget::OpenMenu(this->ObjectSelectMenu);
      };

      MenuTexture = std::make_shared<sf::Texture>();
      MenuTexture->loadFromFile("./SFEngine/Samples/Textures/UI/MenuCallAnimation.png");


      TestScreen = UI::MenuScreen::Create();
      TestScreen->SetBGColor(sf::Color(186, 186, 186, 100));
      TestScreen->SetBGOutlineColor(sf::Color(73, 73, 73));
      TestScreen->SetBGOutlineThickness(-1);
      TestScreen->SetBGPosition({ 0, 0 });
      TestScreen->SetBGSize({ 900, 900 });

      TestScreen2 = UI::MenuScreen::Create();
      TestScreen2->SetBGColor(sf::Color(45, 61, 59));
      TestScreen2->SetBGOutlineColor(sf::Color(73, 73, 73, 100));
      TestScreen2->SetBGOutlineThickness(-1);
      TestScreen2->SetBGPosition({ 0, 0 });
      TestScreen2->SetBGSize({ 900, 900 });

      TestScreen3 = UI::MenuScreen::Create();
      TestScreen3->SetBGColor(sf::Color(61, 45, 51));
      TestScreen3->SetBGOutlineColor(sf::Color(102, 75, 85, 100));
      TestScreen3->SetBGOutlineThickness(-1);
      TestScreen3->SetBGPosition({ 0, 0 });
      TestScreen3->SetBGSize({ 900, 900 });

      TestMenu = UI::MenuWidget::Create(UILayer, UIHelper, { 0, 0 }, { 900, 900 });
      UI::MenuWidget::SetFont(TestMenu, MenuFont);
      UI::MenuWidget::SetTitle(TestMenu, "Test Menu", 16, sf::Color(140, 0, 51));

      assert(TestMenu && TestMenu->Helper.lock() && TestMenu->MyLayer.lock());
      UI::MenuWidget::SetDefaultScreen(TestScreen, TestMenu);
      UI::MenuWidget::AddScreen(TestScreen2, TestMenu);
      UI::MenuWidget::AddScreen(TestScreen3, TestMenu);

      TestScreenButton1 = UI::ClickButtonBase::Create(TestScreen->ScreenLayer, TestScreen->ScreenHelper, { 0, 800 }, { 150, 45 });
      TestScreenButton1->SetBGOutlineColor(sf::Color(58, 0, 21)); TestScreenButton1->SetBGOutlineColorHighlighted(sf::Color(132, 0, 48));
      TestScreenButton1->MouseReleaseCB = [this]() { this->TestMenu->CloseMenu(); };
      auto txtlabel1 = UI::TextLabel::Create(TestScreenButton1, TestScreenButton1->Helper, UI::TextAlignment::CenterJustified, "Close Menu", sf::Color(63, 0, 23), MenuFont, 24, { 0,0,1000,1000 }, { 0,0 });

      TestScreenButton2 = UI::ClickButtonBase::Create(TestScreen->ScreenLayer, TestScreen->ScreenHelper, { 300, 400 }, { 150, 45 });
      TestScreenButton2->SetBGOutlineColor(sf::Color(58, 0, 21)); TestScreenButton2->SetBGOutlineColorHighlighted(sf::Color(132, 0, 48));
      TestScreenButton2->MouseReleaseCB = [this]() { this->TestMenu->ShowScreen(this->TestScreen2); };
      auto txtlabel2 = UI::TextLabel::Create(TestScreenButton2, TestScreenButton2->Helper, UI::TextAlignment::CenterJustified, "Test Screen 2", sf::Color(63, 0, 23), MenuFont, 24, { 0,0,1000,1000 }, { 0,0 });

      TestScreenButton3 = UI::ClickButtonBase::Create(TestScreen2->ScreenLayer, TestScreen2->ScreenHelper, { 300, 300 }, { 150, 45 });
      TestScreenButton3->SetBGOutlineColor(sf::Color(58, 0, 21)); TestScreenButton3->SetBGOutlineColorHighlighted(sf::Color(132, 0, 48));
      TestScreenButton3->MouseReleaseCB = [this]() { this->TestScreen2->CloseScreen(); };
      auto txtlabel3 = UI::TextLabel::Create(TestScreenButton3, TestScreenButton3->Helper, UI::TextAlignment::CenterJustified, "Back", sf::Color(63, 0, 23), MenuFont, 24, { 0,0,1000,1000 }, { 0,0 });

      TestScreenButton4 = UI::ClickButtonBase::Create(TestScreen2->ScreenLayer, TestScreen2->ScreenHelper, { 300, 400 }, { 150, 45 });
      TestScreenButton4->SetBGOutlineColor(sf::Color(58, 0, 21)); TestScreenButton4->SetBGOutlineColorHighlighted(sf::Color(132, 0, 48));
      TestScreenButton4->MouseReleaseCB = [this]() { this->TestMenu->ShowScreen(this->TestScreen3); };
      auto txtlabel4 = UI::TextLabel::Create(TestScreenButton4, TestScreenButton4->Helper, UI::TextAlignment::CenterJustified, "Test Screen 3", sf::Color(63, 0, 23), MenuFont, 24, { 0,0,1000,1000 }, { 0,0 });

      TestScreenButton5 = UI::ClickButtonBase::Create(TestScreen3->ScreenLayer, TestScreen3->ScreenHelper, { 300, 300 }, { 150, 45 });
      TestScreenButton5->SetBGOutlineColor(sf::Color(58, 0, 21)); TestScreenButton5->SetBGOutlineColorHighlighted(sf::Color(132, 0, 48));
      TestScreenButton5->MouseReleaseCB = [this]() { this->TestScreen3->CloseScreen(); };
      auto txtlabel5 = UI::TextLabel::Create(TestScreenButton5, TestScreenButton5->Helper, UI::TextAlignment::CenterJustified, "Back", sf::Color(63, 0, 23), MenuFont, 24, { 0,0,1000,1000 }, { 0,0 });

      TestScreenButton6 = UI::ClickButtonBase::Create(TestScreen3->ScreenLayer, TestScreen3->ScreenHelper, { 300, 400 }, { 150, 45 });
      TestScreenButton6->SetBGOutlineColor(sf::Color(58, 0, 21)); TestScreenButton6->SetBGOutlineColorHighlighted(sf::Color(132, 0, 48));
      TestScreenButton6->MouseReleaseCB = [this]() { this->TestMenu->CloseMenu(); };
      auto txtlabel6 = UI::TextLabel::Create(TestScreenButton6, TestScreenButton6->Helper, UI::TextAlignment::CenterJustified, "Close Menu", sf::Color(63, 0, 23), MenuFont, 24, { 0,0,1000,1000 }, { 0,0 });

      assert(TestMenu && TestScreen);
    }
    catch (std::exception &err)
    {
      std::cerr << "Fuck: " << err.what() << std::endl;
    }


  }

  Editor::~Editor()
  {
    TestMenu->Close();
  }

  void Editor::TickUpdate(const double &delta)
  {

    UIHelper->TickUpdate(delta);
  }

  void Editor::Render()
  {
    //currentRenderWindow->clear(sf::Color::Black);
    PreviewTexture.clear(sf::Color::Transparent);
    UITexture->clear(sf::Color::Black);


    UIHelper->Render(UITexture);


    //PreviewTexture.display();

    ////draw UI elements
    //TestButton->Render(UITexture);

    UITexture->display();

    UISprite.setTexture(UITexture->getTexture());

    currentRenderWindow->draw(EditorModeText);

    currentRenderWindow->draw(UISprite);

    currentRenderWindow->display();
  }


}
