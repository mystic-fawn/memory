#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;




char ***arr;// dynamic array for the game
int d1, d2, d3;
int Size, n, youIndex;
int *scores, score;// for score
int numx, numy, numx1, numy1;
string *names, name;// for names
string lettres = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzzAABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTTUUVVWWXXYYZZ";
string namedoc, themes, rep;
fstream f;
bool run, msgwin; // bool for run loop;
bool save = false;
sf::Font font;
sf::Vector2f position;
sf::RenderWindow window(sf::VideoMode(1200, 800), "Memory image");
sf::View view(sf::FloatRect(0, 0, 1200.f, 800.f));

sf::VertexArray m_vertices;
sf::Texture m_tileset;
string letters ="abcdefghijklmnopqr#";


void maps(sf::Vector2u tileSize, sf::Vector2u textureSize);
void verify(int y, int x, int y1, int x1);
void cache(int y, int x);
bool boucle();

int main()
{
/****************************Choice Of Difficulty Mode**************************/
	//text1
	font.loadFromFile("res/arial.ttf");
	string msg1 = "easy";
	sf::Text text1;
	text1.setFont(font);
	text1.setString(msg1);
	sf::Vector2u winSize = window.getSize();
	text1.setCharacterSize(24);
	text1.setFillColor(sf::Color(0, 0, 255));
	// text2
	string msg2 = "hard";
	sf::Text text2;
	text2.setFont(font);
	text2.setString(msg2);
	text2.setCharacterSize(24);
	text2.setFillColor(sf::Color(0, 0, 255));
	// textBox
	sf::Vector2f position;
	sf::RectangleShape shape1;
	shape1.setSize(sf::Vector2f(text1.getLocalBounds().width, 26.f));
	shape1.setFillColor(sf::Color(0, 0, 0));
	sf::Vector2f position2;
	sf::RectangleShape shape2;
	shape2.setSize(sf::Vector2f(text2.getLocalBounds().width, 26.f));
	shape2.setFillColor(sf::Color(0, 0, 0));
	//
	sf::Vector2i mousePosition;
	sf::Vector2f worldPos;
	int difficulty;
	run = true;
	while (run)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					run = false;
					break;
				case sf::Event::Resized:
					//text1.setPosition(sf::Vector2f(winSize.x / 2 - msg1.size(), winSize.y / 2));
					view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
					text1.setPosition(sf::Vector2f(view.getSize().x / 4 - msg1.size(), view.getSize().y / 2 - msg1.size()));
					text2.setPosition(sf::Vector2f(view.getSize().x / 1.5 - msg2.size(), view.getSize().y / 2 - msg2.size()));
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Q:
							run = false;
							break;
					}
				case sf::Event::MouseMoved:
					mousePosition = sf::Mouse::getPosition(window);
					worldPos = window.mapPixelToCoords(mousePosition);
					if (worldPos.x > shape1.getPosition().x && worldPos.x < shape1.getPosition().x + shape1.getSize().x
					&& worldPos.y > shape1.getPosition().y && worldPos.y < shape1.getPosition().y + shape1.getSize().y)
					{
						shape1.setFillColor(sf::Color(255, 255, 255));
						shape2.setFillColor(sf::Color(0, 0, 0));
						break;
					}else if (worldPos.x > shape2.getPosition().x && worldPos.x < shape2.getPosition().x + shape2.getSize().x
					&& worldPos.y > shape2.getPosition().y && worldPos.y < shape2.getPosition().y + shape2.getSize().y)
					{
						shape2.setFillColor(sf::Color(255, 255, 255));
						shape1.setFillColor(sf::Color(0, 0, 0));
						break;
					}else
					{
						shape1.setFillColor(sf::Color(0, 0, 0));
						shape2.setFillColor(sf::Color(0, 0, 0));
						break;
					}
				case sf::Event::MouseButtonPressed:
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Left:
							if(worldPos.x >= shape1.getPosition().x && worldPos.x <= shape1.getPosition().x + shape1.getSize().x
							&& worldPos.y >= shape1.getPosition().y && worldPos.y <= shape1.getPosition().y + shape1.getSize().y)
							{
								difficulty = 1;
								run = false;
								break;
							}
							if(worldPos.x > shape2.getPosition().x && worldPos.x < shape2.getPosition().x + shape2.getSize().x
							&& worldPos.y > shape2.getPosition().y && worldPos.y < shape2.getPosition().y + shape2.getSize().y)
							{
								difficulty = 2;
								run = false;
								break;
							}
							break;
						default:
							break;
					}

				default:
					break;
			}
		}
		position = text1.getPosition();
		shape1.setPosition(position.x, position.y + 2);
		position2 = text2.getPosition();
		shape2.setPosition(position2.x, position2.y + 2);
		window.setView(view);
		window.clear();
		window.draw(shape1);
		window.draw(shape2);
		window.draw(text1);
		window.draw(text2);
		window.display();
	}
/****************************Choix du theme ************************************/
// case du tableau
sf::Vector2u tileSize;
tileSize = sf::Vector2u(47*2, 62*2);
sf::Vector2u textureSize;
textureSize = sf::Vector2u(47, 62);

// le text
	int theme = 0;
	msg1 = "classic";
	text1.setString(msg1);
	text1.setFillColor(sf::Color(200, 200, 200));
	msg2 = "Avatar";
	text2.setString(msg2);
	text2.setFillColor(sf::Color(200, 200, 200));
	string msg3 = "Pokemon";
	sf::Text text3;
	text3.setString(msg3);
	text3.setFillColor(sf::Color(200, 200, 200));
	text3.setFont(font);
	text3.setCharacterSize(24);
	shape1.setSize(sf::Vector2f(view.getSize().x / 3, 26.f));
	shape1.setFillColor(sf::Color(0, 0, 50));
	shape1.setPosition(sf::Vector2f(view.getSize().x / 3, view.getSize().y / 2.25));
	text1.setPosition(sf::Vector2f(shape1.getPosition().x - text1.getLocalBounds().width / 2 + shape1.getSize().x / 2, shape1.getPosition().y));
	shape2.setSize(sf::Vector2f(view.getSize().x / 3, 26.f));
	shape2.setFillColor(sf::Color(0, 0, 50));
	shape2.setPosition(sf::Vector2f(shape1.getPosition().x, shape1.getPosition().y + 2 * shape1.getSize().y));
	text2.setPosition(sf::Vector2f(shape2.getPosition().x - text2.getLocalBounds().width / 2 + shape2.getSize().x / 2, shape2.getPosition().y));
	sf::RectangleShape shape3;
	shape3.setSize(sf::Vector2f(view.getSize().x / 3, 26.f));
	shape3.setFillColor(sf::Color(0, 0, 50));
	shape3.setPosition(sf::Vector2f(shape2.getPosition().x, shape2.getPosition().y + 2 * shape2.getSize().y));
	text3.setPosition(sf::Vector2f(shape3.getPosition().x - text3.getLocalBounds().width / 2 + shape3.getSize().x / 2, shape3.getPosition().y));

	if(window.isOpen())
		run = true;
	while(run)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					run = false;
					break;
				case sf::Event::MouseMoved:
				mousePosition = sf::Mouse::getPosition(window);
				worldPos = window.mapPixelToCoords(mousePosition);
				if (worldPos.x > shape1.getPosition().x && worldPos.x < shape1.getPosition().x + shape1.getSize().x
				&& worldPos.y > shape1.getPosition().y && worldPos.y < shape1.getPosition().y + shape1.getSize().y)
				{
					shape1.setFillColor(sf::Color(0, 0, 255));
					shape2.setFillColor(sf::Color(0, 0, 50));
					break;
				}else if (worldPos.x > shape2.getPosition().x && worldPos.x < shape2.getPosition().x + shape2.getSize().x
				&& worldPos.y > shape2.getPosition().y && worldPos.y < shape2.getPosition().y + shape2.getSize().y)
				{
					shape2.setFillColor(sf::Color(0, 0, 255));
					shape1.setFillColor(sf::Color(0, 0, 50));
					break;
				}else if (worldPos.x > shape3.getPosition().x && worldPos.x < shape3.getPosition().x + shape3.getSize().x
				&& worldPos.y > shape3.getPosition().y && worldPos.y < shape3.getPosition().y + shape3.getSize().y)
				{
						shape3.setFillColor(sf::Color(0, 0, 255));
						shape1.setFillColor(sf::Color(0, 0, 50));
						shape2.setFillColor(sf::Color(0, 0, 50));
						break;
				}else
				{
					shape1.setFillColor(sf::Color(0, 0, 50));
					shape2.setFillColor(sf::Color(0, 0, 50));
					shape3.setFillColor(sf::Color(0, 0, 50));
					break;
				}
			case sf::Event::MouseButtonPressed:
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Left:
							if(worldPos.x >= shape1.getPosition().x && worldPos.x <= shape1.getPosition().x + shape1.getSize().x
							&& worldPos.y >= shape1.getPosition().y && worldPos.y <= shape1.getPosition().y + shape1.getSize().y)
							{
								theme = 0;
								run = false;
								break;
							}
							else if(worldPos.x >= shape2.getPosition().x && worldPos.x <= shape2.getPosition().x + shape2.getSize().x
										&& worldPos.y > shape2.getPosition().y && worldPos.y < shape2.getPosition().y + shape2.getSize().y)
										{
							theme = 1;
							run = false;
							break;
						}else if (worldPos.x > shape3.getPosition().x && worldPos.x < shape3.getPosition().x + shape3.getSize().x
						&& worldPos.y > shape3.getPosition().y && worldPos.y < shape3.getPosition().y + shape3.getSize().y)
						{
							theme = 2;
							run = false;
						}
					}
					break;
				default:
					break;
			}
		}
		window.clear();
		window.draw(shape1);
		window.draw(shape2);
		window.draw(shape3);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.display();
	}
	switch(theme)
	{
		case 0:
			themes = "res/cards.png";
			tileSize = sf::Vector2u(47*2, 62*2);
			textureSize = sf::Vector2u(47, 62);
			break;
		case 1:
			themes = "res/avatar.png";
			textureSize = sf::Vector2u(80, 80);
			tileSize = sf::Vector2u(textureSize.x * 1.5, textureSize.y * 1.5);
			break;
		case 2:
			themes = "res/pokemon.png";
			textureSize = sf::Vector2u(100, 100);
			tileSize = sf::Vector2u(textureSize.x * 1.20, textureSize.y * 1.20);
			break;
	}
/****************************generation of memory*******************************/
switch (difficulty){
	case 1:
		Size = 4;
		lettres.erase(Size*Size);
		namedoc = "res/scoreBoard_easy.txt";
		break;
	case 2:
		Size = 6;
		namedoc = "res/scoreBoard_hard.txt";
		lettres.erase(Size*Size);
		break;
	default:
		Size = 4;
		lettres.erase(Size*Size);
		namedoc = "res/scoreBoard_easy.txt";
		break;
}
// Initialisation du Memory
	d1 = Size;
	d2 = Size;
	d3 = 2;
	arr = new char **[d1];
	for (int i = 0; i < d1; i++){
		arr[i] = new char *[d2];
		for (int j = 0; j < d2; j++){
			arr[i][j] = new char [d3];
		}
	}
// Remplissage du tableau
	srand((unsigned int)time(NULL));
	for (int i = 0; i < d2; i++){
		for (int j = 0; j < d2; j++){
			int num = rand() % lettres.length();
			arr[j][i][0] = lettres[num];
			arr[j][i][1] = '#';
			lettres.erase(num, 1);
		}
	}


/*******************************************************************************/
maps(tileSize, textureSize);

/****************************Game Loop**************************************/
  int turn = 0;
	if (window.isOpen())
	run = true;
	if (difficulty == 2)
	{
		view.move(-240, -30);
}else{
	view.move(-350, -150);
}
	while (run)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					run = false;
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Q:
							run = false;
							break;
						case sf::Keyboard::Left:
							view.move(-10, 0);
							break;
						case sf::Keyboard::Right:
							view.move(10, 0);
							break;
						case sf::Keyboard::Up:
							view.move(0, -10);
							break;
						case sf::Keyboard::Down:
							view.move(0, 10);
							break;
					}
        case sf::Event::MouseMoved:
          mousePosition = sf::Mouse::getPosition(window);
          worldPos = window.mapPixelToCoords(mousePosition);
          break;

        case sf::Event::MouseButtonPressed:
          switch (event.mouseButton.button)
          {
            case sf::Mouse::Left:
						if (turn == 2)
						{
							verify(numx, numy, numx1, numy1);
							turn = 0;
						}

              for (int i = 0; i < d1; i++)
                for (int j = 0; j < d2; j++)
                    {
                      if (worldPos.x > i * tileSize.x + 10 && worldPos.x < (i + 1) * tileSize.x
                      && worldPos.y > j * tileSize.y + 10 && worldPos.y < (j + 1) * tileSize.y)
                      {
												if (turn == 0)
												{
													if (arr[j][i][1] == arr[j][i][0]){
														turn--;}else{
													arr[j][i][1] = arr[j][i][0];
													numx = j, numy = i;}
												}else{
													numx1 = j, numy1 = i;
													if(numx1 == numx && numy1 == numy || arr[j][i][1] == arr[j][i][0]){
														turn--;
													}else
													{
														arr[j][i][1] = arr[j][i][0];
													}

												}
												turn++;
                      	break;
                    }
									}
              break;
            default :
              break;
          }
				default:
					break;
			}
		}


		maps(tileSize, textureSize);
		window.setView(view);
		window.clear();
		window.draw(m_vertices, &m_tileset);
		window.display();
		boucle();
	}
/****************************Affichage message de victoire**********************/
	font.loadFromFile("res/arial.ttf");
	msg1 = "Bravo !!!";
	text1.setFont(font);
	text1.setString(msg1);
	winSize = window.getSize();
	text1.setCharacterSize(24);
	text1.setFillColor(sf::Color(0, 0, 255));
	if(window.isOpen())
		run = true;
		if (difficulty == 2)
		{
			view.move(240, 30);
	}else{
		view.move(350, 150);
	}
	while (run)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					run = false;
					break;
				case sf::Event::Resized:
					//text1.setPosition(sf::Vector2f(winSize.x / 2 - msg1.size(), winSize.y / 2));
					view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
					text1.setPosition(sf::Vector2f(view.getSize().x / 4 - msg1.size(), view.getSize().y / 2 - msg1.size()));
					break;
				case sf::Event::KeyPressed:
						run = false;
						break;
				case sf::Event::MouseButtonPressed:
					run = false;
					break;
				default:
					break;
			}
		}
		window.setView(view);
		window.clear();
		window.draw(text1);
		window.display();
	}
/****************************Récupération des donnees devsauvegarde*************/

	f.open(namedoc);
	while(!f.eof())
	{
		string b;
		f >> b >> b;
		n++;
	}
	f.close();
	if (n < 1)
	{
		n = 1;
	}
	scores = new int[n];
	names = new string[n];

	f.open(namedoc);
	if (n != 1)
	{
		for (int i = 0; i < n; i++)
			{f >> names[i]; f >> scores[i];}
	}
	names [n-1] = " ";
	scores [n-1] = score;
	//comparaison des score
	youIndex = n-1;
	if (n > 1)
	{
		int a;
		  for (int i = 0; i < n; ++i) {
		    int min = scores[i];
		    int minIndex = i;
		    string newName = names[i];
		    for (int j = i+1; j < n; ++j) {
		      if (scores[j] < min) {
						if (youIndex == j)
							youIndex = i;
		        minIndex = j;
		        min = scores[j];
		        newName = names[j];
						a = j;
		      }
		    }
		    if (minIndex != i) {
		      scores[minIndex] = scores[i];
		      names[minIndex] = names[i];
		      scores[i] = min;
		      names[i] = newName;
		    }
		  }
	}
	f.close();

/****************************ScoreBoard display*********************************/
	string rep; //récupérer le nom du joueur;
	names[youIndex] = rep;
	//Le tableaux
	sf::RectangleShape line1, line2, line3, line4, line5, line6, line7, line8, line9;
	//ligne verticales
	line1.setSize(sf::Vector2f(5, 600));
	line2.setSize(sf::Vector2f(5, 600));
	line3.setSize(sf::Vector2f(5, 600));
	line1.setPosition(sf::Vector2f(view.getSize().x / 4, view.getSize().y / 16));
	line2.setPosition(sf::Vector2f(line1.getPosition().x + 300, line1.getPosition().y));
	line3.setPosition(sf::Vector2f(line2.getPosition().x + 300, line1.getPosition().y));
	line1.setFillColor(sf::Color(0, 255, 0));
	line2.setFillColor(sf::Color(0, 255, 0));
	line3.setFillColor(sf::Color(0, 255, 0));

	//Ligne horizontales
	line4.setSize(sf::Vector2f(605, 5));
	line5.setSize(sf::Vector2f(605, 5));
	line6.setSize(sf::Vector2f(605, 5));
	line7.setSize(sf::Vector2f(605, 5));
	line8.setSize(sf::Vector2f(605, 5));
	line9.setSize(sf::Vector2f(605, 5));
	line4.setPosition(sf::Vector2f(line1.getPosition().x, line1.getPosition().y));
	line5.setPosition(sf::Vector2f(line1.getPosition().x, line1.getPosition().y + line1.getSize().y / 5));
	line6.setPosition(sf::Vector2f(line1.getPosition().x, line1.getPosition().y + line1.getSize().y / 2.5));
	line7.setPosition(sf::Vector2f(line1.getPosition().x, line1.getPosition().y + line1.getSize().y / 1.67));
	line8.setPosition(sf::Vector2f(line1.getPosition().x, line1.getPosition().y + line1.getSize().y / 1.25));
	line9.setPosition(sf::Vector2f(line1.getPosition().x, line1.getPosition().y + line1.getSize().y));
	line4.setFillColor(sf::Color(0, 255, 0));
	line5.setFillColor(sf::Color(0, 255, 0));
	line6.setFillColor(sf::Color(0, 255, 0));
	line7.setFillColor(sf::Color(0, 255, 0));
	line8.setFillColor(sf::Color(0, 255, 0));
	line9.setFillColor(sf::Color(0, 255, 0));
	//récupération des noms
	sf::Text name1, name2, name3, name4, name5;
	name1.setString(names[0]);
	if(n > 1)
	name2.setString(names[1]);
	if(n > 2)
	name3.setString(names[2]);
	if(n > 3)
	name4.setString(names[3]);
	if(n > 4)
	name5.setString(names[4]);
	name1.setFont(font);
	name2.setFont(font);
	name3.setFont(font);
	name4.setFont(font);
	name5.setFont(font);
 	name1.setFillColor(sf::Color(0, 255, 0));
 	name2.setFillColor(sf::Color(0, 255, 0));
 	name3.setFillColor(sf::Color(0, 255, 0));
 	name4.setFillColor(sf::Color(0, 255, 0));
 	name5.setFillColor(sf::Color(0, 255, 0));
	name1.setPosition(sf::Vector2f(line1.getPosition().x + 25, (line4.getPosition().y + line5.getPosition().y) / 2));
	name2.setPosition(sf::Vector2f(line1.getPosition().x + 25, (line6.getPosition().y + line5.getPosition().y) / 2));
	name3.setPosition(sf::Vector2f(line1.getPosition().x + 25, (line7.getPosition().y + line6.getPosition().y) / 2));
	name4.setPosition(sf::Vector2f(line1.getPosition().x + 25, (line8.getPosition().y + line7.getPosition().y) / 2));
	name5.setPosition(sf::Vector2f(line1.getPosition().x + 25, (line9.getPosition().y + line8.getPosition().y)/ 2));
	//récupération des scores
	sf::Text score1, score2, score3, score4, score5;
	score1.setString(to_string(scores[0]));
	if(n > 1)
	score2.setString(to_string(scores[1]));
	if(n > 2)
	score3.setString(to_string(scores[2]));
	if(n > 3)
	score4.setString(to_string(scores[3]));
	if(n > 4)
	score5.setString(to_string(scores[4]));
	score1.setFont(font);
	score2.setFont(font);
	score3.setFont(font);
	score4.setFont(font);
	score5.setFont(font);
	score1.setFillColor(sf::Color(0, 255, 0));
	score2.setFillColor(sf::Color(0, 255, 0));
	score3.setFillColor(sf::Color(0, 255, 0));
	score4.setFillColor(sf::Color(0, 255, 0));
	score5.setFillColor(sf::Color(0, 255, 0));
	score1.setPosition(sf::Vector2f(line2.getPosition().x + 25, (line4.getPosition().y + line5.getPosition().y) / 2));
	score2.setPosition(sf::Vector2f(line2.getPosition().x + 25, (line6.getPosition().y + line5.getPosition().y) / 2));
	score3.setPosition(sf::Vector2f(line2.getPosition().x + 25, (line7.getPosition().y + line6.getPosition().y) / 2));
	score4.setPosition(sf::Vector2f(line2.getPosition().x + 25, (line8.getPosition().y + line7.getPosition().y) / 2));
	score5.setPosition(sf::Vector2f(line2.getPosition().x + 25, (line9.getPosition().y + line8.getPosition().y)/ 2));
	if (window.isOpen())
	run = true;

	while (run)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					run = false;
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::A:
							rep += "a";
							break;
						case sf::Keyboard::Z:
							rep += "z";
							break;
						case sf::Keyboard::E:
							rep += "e";
							break;
						case sf::Keyboard::R:
							rep += "r";
							break;
						case sf::Keyboard::T:
							rep += "t";
							break;
						case sf::Keyboard::Y:
							rep += "y";
							break;
						case sf::Keyboard::U:
							rep += "u";
							break;
						case sf::Keyboard::I:
							rep += "i";
							break;
						case sf::Keyboard::O:
							rep += "o";
							break;
						case sf::Keyboard::P:
							rep += "p";
							break;
						case sf::Keyboard::S:
							rep += "s";
							break;
						case sf::Keyboard::D:
							rep += "d";
							break;
						case sf::Keyboard::F:
							rep += "f";
							break;
						case sf::Keyboard::G:
							rep += "g";
							break;
						case sf::Keyboard::H:
							rep += "h";
							break;
						case sf::Keyboard::J:
							rep += "j";
							break;
						case sf::Keyboard::K:
							rep += "k";
							break;
						case sf::Keyboard::L:
							rep += "l";
							break;
						case sf::Keyboard::M:
							rep += "m";
							break;
						case sf::Keyboard::W:
							rep += "w";
							break;
						case sf::Keyboard::X:
							rep += "x";
							break;
						case sf::Keyboard::C:
							rep += "c";
							break;
						case sf::Keyboard::V:
							rep += "v";
							break;
						case sf::Keyboard::B:
							rep += "b";
							break;
						case sf::Keyboard::N:
							rep += "n";
							break;
						case sf::Keyboard::Q:
							rep += "q";
							break;
						case sf::Keyboard::Num1:
							rep += "1";
							break;
						case sf::Keyboard::Num2:
							rep += "2";
							break;
						case sf::Keyboard::Num3:
							rep += "3";
							break;
						case sf::Keyboard::Num4:
						case sf::Keyboard::Quote:
							rep += "4";
							break;
						case sf::Keyboard::Num5:
							rep += "5";
							break;
						case sf::Keyboard::Num6:
						case sf::Keyboard::Hyphen:
							rep += "6";
							break;
						case sf::Keyboard::Num7:
							rep += "7";
							break;
						case sf::Keyboard::Num8:
							rep += "8";
							break;
						case sf::Keyboard::Num9:
							rep += "9";
							break;
						case sf::Keyboard::Num0:
							rep += "0";
							break;
						case sf::Keyboard::Enter:
							run = false;
							save = true;
							break;
						case sf::Keyboard::Backspace:
							rep.erase(rep.length()-1);
							break;
					}
				default:
					break;
			}
		}
						names[youIndex] = rep;
		name1.setString(names[0]);
		if(n > 1)
		name2.setString(names[1]);
		if(n > 2)
		name3.setString(names[2]);
		if(n > 3)
		name4.setString(names[3]);
		if(n > 4)
		name5.setString(names[4]);
		window.clear();
		window.draw(line1);
		window.draw(line2);
		window.draw(line3);
		window.draw(line4);
		window.draw(line5);
		window.draw(line6);
		window.draw(line7);
		window.draw(line8);
		window.draw(line9);
		window.draw(name1);
		window.draw(name2);
		window.draw(name3);
		window.draw(name4);
		window.draw(name5);
		window.draw(score1);
		window.draw(score2);
		window.draw(score3);
		window.draw(score4);
		window.draw(score5);
		window.display();
	}

/****************************Sauvegarde des scores******************************/
if(save)
{
if (names[youIndex] == " " || names[youIndex] == "guest" || names[youIndex] == "")
	names[youIndex] = "guest";
f.open(namedoc);
for (int i = 0; i < n; ++i) {
	if (i < 5)
  f << names[i] << " " << scores[i] << endl;}
}
f.close();
/****************************Déstruction du tableau*****************************/
	for (int i = 0; i < d1; i++){
		for (int j = 0; j < d2; j++){
			delete [] arr[i][j];
		}
		delete [] arr[i];
	}
	delete [] arr;
	delete [] names;
	delete [] scores;
	window.close();
	return 0;
}


void maps(sf::Vector2u tileSize, sf::Vector2u textureSize){
m_tileset.loadFromFile(themes);

int count = 0;
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(d1 * d2 * 4);
	for (int i = 0; i < d1; i++){
	  for (int j = 0; j < d2; j++){
	    for (int k = 0; k < letters.length(); k++)
	    {
	      if (arr[j][i][1] == letters[k])
	      {
	        int tu = k % (m_tileset.getSize().x / textureSize.x);
	        int tv = k / (m_tileset.getSize().x / textureSize.x);

	        sf::Vertex* quad = &m_vertices[count * 4];

	        quad[0].position = sf::Vector2f(i * tileSize.x + 10, j * tileSize.y + 10);
	        quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y + 10);
	        quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
	        quad[3].position = sf::Vector2f(i * tileSize.x + 10, (j + 1) * tileSize.y);

	        quad[0].texCoords = sf::Vector2f(tu * textureSize.x, tv * textureSize.y);
	        quad[1].texCoords = sf::Vector2f((tu + 1) * textureSize.x, tv * textureSize.y);
	        quad[2].texCoords = sf::Vector2f((tu + 1) * textureSize.x, (tv + 1) * textureSize.y);
	        quad[3].texCoords = sf::Vector2f(tu * textureSize.x, (tv + 1) * textureSize.y);

	        }

	      }
	          count++;
	    }
	  }
}

void cache(int x, int y){
  arr[x][y][1] = '#';

}
void verify(int x, int y, int x1, int y1){
  if (arr[x][y][1] != arr[x1][y1][1]){
    cache(x, y); cache(x1, y1);
  }
  if (x == x1 && y == y1){
    cache(x, y); cache(x1, y1);
  }
	 score++;
}


bool boucle(){
  int win = 0;
  for (int i = 0; i < d2; i++){
    for (int j = 0; j < d1; j++){
      if (arr[j][i][1] != '#'){
        win++;
      }
    }
  }
  if (win == Size*Size){
    run = false;
		save = true;
		msgwin = true;
  }else {
		run = true;
		if (!window.isOpen())
		run = false;
		msgwin = false;}
return run;}
