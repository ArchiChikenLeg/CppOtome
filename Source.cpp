#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <locale>
#include <fstream>
#include <codecvt>

using namespace sf;
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

class Object {
private:
	Sprite form;
	bool isfind = 0;
	float x;
	float y;
	Texture teaText;
public:
	Object() {
		teaText.loadFromFile("C:\\Users\\andri\\Game\\tea.png");
		form.setTexture(teaText);
		x = 100;
		y = 100;
		form.setPosition(x,y);
		form.setScale(0.25f,0.25f);
	}
	Sprite Form() {
		return form;
	}
	bool isFind() {
		return isfind;
	}
	void setFind(bool i) {
		isfind = i;
	}
	void setPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

class Dialog {
private:
	RectangleShape form;
	Text text;
	Font font;
	bool chosen = 0;
	bool i;
public:
	Dialog() {
		font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
		i = 0;
		text.setString(" ");
		form.setSize(Vector2f(200.f, 100.f));
		form.setFillColor(Color(125, 125, 125));
		form.setPosition(620.f, 250.f + i * 120);
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(Color::White);
		text.setPosition(form.getPosition());
	}
	Dialog(string title, bool i) {
		font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
		this->i = i;
		this->text.setString(title);
		form.setSize(Vector2f(200.f, 100.f));
		form.setFillColor(Color(125, 125, 125));
		form.setPosition(620.f, 250.f + i * 120);
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(Color::White);
		text.setPosition(form.getPosition());
	}
	RectangleShape getForm() {
		return form;
	}
	Text getText() {
		return text;
	}
	void setChosen(bool choose) {
		chosen = choose;
	}
	void setData(string s, bool i) {
		text.setString(s);
		this->i = i;
		form.setPosition(620.f, 250.f + i * 120);
		text.setPosition(form.getPosition());
	}
	bool getChosen() {
		return chosen;
	}
	void draw(RenderWindow &window) {
		window.draw(form);
		window.draw(text);
	}
};

class Character {
private:
	string textureappfile;
	Texture app;
	Sprite appearance;
	string texturescenefile;
	Texture scene;
	Sprite basescene;
	Text bottomtext[5];
	int relationbar=50;
	bool endscene=0;
	Dialog var1;
	Dialog var2;
public:
	Character(string &appfile, string &scenefile, Font &font, string v1, string v2) {
		textureappfile = appfile;
		app.loadFromFile(textureappfile);
		appearance.setTexture(app);
		appearance.setTextureRect(IntRect(0, 0, 483, 755));
		texturescenefile = scenefile;
		scene.loadFromFile(texturescenefile);
		basescene.setTexture(scene);
		basescene.setTextureRect(IntRect(0, 0, 1920, 1080));
		wifstream Ltext("Ltext.txt");
		wstring title;
		Ltext.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		int index=0;
		for (int i = 0; i < 5; i++) {
			bottomtext[i].setFont(font);
			bottomtext[i].setCharacterSize(24);
			bottomtext[i].setFillColor(Color::White);
			bottomtext[i].setPosition(10, 650);
			getline(Ltext, title);
			bottomtext[i].setString(title);
		}
		var1.setData(v1, 0);
		var2.setData(v2, 1);
	}
	void setPosition(int ax, int ay) {
		appearance.setPosition(ax, ay);
	}
	Sprite getAppearance() {
		return appearance;
	}
	Sprite getBaseScene() {
		return basescene;
	}
	void setEndingScene(bool end) {
		endscene = end;
	}
	bool IsEnded() {
		return endscene;
	}
	Text getText(int i) {
		return bottomtext[i];
	}
	friend void CharacterScene(Character &Char, RenderWindow &window, RectangleShape &bottompanel, int &sceneState);
};

void CharacterScene(Character &Char, RenderWindow &window, RectangleShape &bottompanel, int &sceneState) {
	window.draw(Char.getBaseScene());
	Text bottomtext;
	switch (sceneState) {
	case 0:
		bottomtext = Char.getText(sceneState);
		break;
	case 1:
		bottomtext = Char.getText(sceneState);
		window.draw(Char.getAppearance());
		break;
	case 2:
		bottomtext = Char.getText(sceneState);
		window.draw(Char.getAppearance());
		break;
	case 3:
		bottomtext = Char.getText(sceneState);
		window.draw(Char.getAppearance());
		break;
	case 4:
		bottomtext = Char.getText(sceneState);
		window.draw(Char.getAppearance());
		break;
	case 5:
		Char.var1.draw(window);
		Char.var2.draw(window);
		Event newevent;
		newevent.type == Event::MouseButtonPressed;
		if (!Char.var1.getChosen() && !Char.var2.getChosen())
		{
			if (window.waitEvent(newevent) && newevent.mouseButton.button == Mouse::Left)
			{
				cout << "click\n";
				if (newevent.mouseButton.x <= 820 && newevent.mouseButton.x >= 620) {
					if (newevent.mouseButton.y >= 250 && newevent.mouseButton.y <= 350)
						Char.var1.setChosen(1);
					else
						Char.var2.setChosen(1);
				}
				cout << Char.var1.getChosen() << " " << Char.var2.getChosen();
			}
		}
		if (Char.var2.getChosen())
			sceneState++;
		break;
	case 6:
		sceneState++;
		break;
	case 7:
		window.draw(Char.getAppearance());
		break;
	default:
		break;
	}
	if (sceneState < 5) {
		window.draw(bottompanel);
		window.draw(bottomtext);
	}
	window.display();
	Event newevent;
	newevent.type == Event::MouseButtonPressed;
	if (sceneState < 8) {
		if (window.waitEvent(newevent) && newevent.mouseButton.button == Mouse::Left) {
			sceneState++;
			cout << "click";
			if(sceneState<5)
				sleep_for(170ms);
		}
	}
}

void FindingScene(RenderWindow &window, Sprite &background, Object* obj) {
	!obj[0].isFind() ? window.draw(obj[0].Form()) : window.draw(background);
	window.display();
	Event newevent;
	newevent.type = Event::MouseButtonPressed;
	if (!obj[0].isFind()) {
		if (window.waitEvent(newevent) && newevent.mouseButton.button == Mouse::Left && newevent.mouseButton.x <= 245 && newevent.mouseButton.x >= 100 && newevent.mouseButton.y <= 300 && newevent.mouseButton.y >= 100) {
			obj[0].setFind(true);
			cout << "click";
			sleep_for(170ms);
		}
	}
}
void startmenu(RenderWindow &window, bool &temp) {
	Texture startmenu;
	startmenu.loadFromFile("C:\\Users\\andri\\Game\\start.jpg");
	Sprite startbackground(startmenu, IntRect(0, 0, 1440, 840));

	RectangleShape buttons[3];
	for (int i = 0; i < 3; i++) {
		buttons[i].setSize(Vector2f(200.f, 100.f));
		buttons[i].setFillColor(Color(125, 125, 125));
		buttons[i].setPosition(620.f, 250.f + i * 120);
	}
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	Text titles[3];
	titles[0].setString("START \nNEW GAME");
	titles[1].setString("RELOAD \nLAST GAME");
	titles[2].setString("EXIT");
	window.clear(Color(20, 0, 0, 0));
	if (temp) {
		for (int i = 0; i < 3; i++) {
			titles[i].setFont(font);
			titles[i].setCharacterSize(24);
			titles[i].setFillColor(Color::White);
			titles[i].setPosition(buttons[i].getPosition());
		}
		window.draw(startbackground);
		for (int i = 0; i < 3; i++) {
			window.draw(buttons[i]);
			window.draw(titles[i]);
		}
		Event event;
		event.type = Event::MouseButtonPressed;
		if (window.waitEvent(event))
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				cout << "click\n";
				if (event.mouseButton.x <= 820 && event.mouseButton.x >= 620) {
					window.clear(Color(20, 0, 0, 0));
					temp = false;
				}
			}
		}
	}
	
	
	window.display();
}
//void basement() {
//	RectangleShape objects[3];
//	for (int i = 0; i < 3; i++) {
//		objects[i].setSize(Vector2f(200.f, 100.f));
//		objects[i].setFillColor(Color(125, 125, 125));
//		objects[i].setPosition(620.f, 250.f + i * 120);
//	}
//	Object obj;
//	int score = 0;
//	int counterobject = 3;
//	for (int i = 0; i < 3; i++)
//		window.draw(objects[i]);
//	window.draw(obj.getForm());
//	/*if (event.type == Event::MouseButtonPressed)
//	{
//		if (event.mouseButton.button == Mouse::Left)
//		{
//			cout << "click\n";
//			while (counterobject > 0) {
//				if (event.mouseButton.x <= 820 && event.mouseButton.x >= 620) {
//					score += 10;
//					counterobject -= 1;
//				}
//			}
//			window.draw(basementscene);
//
//		}
//	}*/
//}
int main()
{
	setlocale(LC_ALL, ".UTF-8");
	system("chcp 1251");

	string basefilename = "C:\\Users\\andri\\Game\\basement.jpg";
	string appLFileName = "C:\\Users\\andri\\Game\\L.png";
	Texture scene;
	scene.loadFromFile(basefilename);
	Texture findBackText;
	findBackText.loadFromFile("C:\\Users\\andri\\Game\\box.png");
	Texture teaText; 
	teaText.loadFromFile("C:\\Users\\andri\\Game\\tea.png");
	Sprite tea;
	tea.setTexture(teaText);
	Sprite basescene;
	basescene.setTexture(scene);
	Sprite findBack;
	findBack.setTexture(findBackText);
	RectangleShape bottompanel(Vector2f(1440, 200));
	bottompanel.setFillColor(Color(127,127,127,200));
	bottompanel.setPosition(0, 640);
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	
	/*string titles[5];
	titles[0] = u8"БУКВЫ ПОХОЖИЕ НА ЗМЕЙ";
	titles[1] = "Џ аҐ­м: \nЉв® вл в Є®©?";
	titles[2] = "Ћ­ ®Ўа вЁ« бў®© ЎҐ§г¬­л© ў§Ј«п¤ ў ¬®о бв®а®­г, ®вўҐа­гўиЁбм ®в ¬®­Ёв®а  - Ґ¤Ё­бвўҐ­­®Ј® Ёбв®з­ЁЄ  бўҐв  ў Є®­гаҐ.";
	titles[3] = "ЏҐаб®­ ¦: \nџ Ї®¬®й­ЁЄ Љ ¬гвбЁ-б ­ , ¬Ґ­п Ї®Їа®бЁ«Ё ЇаЁ­ҐбвЁ д«ҐиЄг б Їа®и«®© бҐаЁЁ.";
	titles[4] = "‹: \n‡Ђ—…Њ? ’л е®зҐим гЄа бвм ¬®о а Ў®вг, ЇаЁ§­ ў ©бп!";*/
	string phrase1="hello";
	string phrase2="bye";
	Character L(appLFileName, basefilename, font, phrase1, phrase2);
	L.setPosition(0, 85);
	int sceneState = 0;
	Object cups[1];
	Object* pcup = cups;

	bool temp = true;
	RenderWindow window(VideoMode(1440, 840), "SFML works!");
	/*ifstream Ltext("Ltext.txt");
	string title;
	getline(Ltext, title);
	cout << title;
	Ltext.close();*/
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (temp)
			startmenu(window, temp);
		else {
			window.draw(basescene);
			CharacterScene(L, window, bottompanel, sceneState);
		}
		////FindingScene(window, basescene, pcup);
		//ifstream Ltext("Ltext.txt");
		////stringstream ss;
		//string title;
		//getline(Ltext, title);
		//cout << title;
		////bottomtext[4].setString(title);
		//Ltext.close();
	}
	return 0;
}