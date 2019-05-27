#include <iostream>
#include <SFML/Graphics.hpp>

#define BOX_SIZE 64
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600
#define BOARD_WIDTH BOX_SIZE * 3
#define BOARD_HEIGHT BOX_SIZE *4

#define BOARD_ORIGIN_X WINDOW_WIDTH/2 - BOARD_WIDTH/2
#define BOARD_ORIGIN_Y WINDOW_HEIGHT/2 - BOARD_HEIGHT/2


enum Turn{
    CROSS,
    CIRCLE,
    VOID
};

bool checkWin(Turn field[][3]);

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "TicTacToe");
    sf::Texture board_texture,cross_texture,circle_texture;
    sf::Sprite board,cross,circle;

    Turn turn = CROSS;
    Turn field[3][3];

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            field[i][j] = VOID;
        }
    }
    cross_texture.loadFromFile("../images/tic_tac_toe_asset.png",sf::IntRect(1 * BOX_SIZE,3 * BOX_SIZE,BOX_SIZE, BOX_SIZE));
    circle_texture.loadFromFile("../images/tic_tac_toe_asset.png",sf::IntRect(0 * BOX_SIZE,3 * BOX_SIZE,BOX_SIZE,BOX_SIZE));
    board_texture.loadFromFile("../images/tic_tac_toe_asset.png",sf::IntRect(0,0,3 * BOX_SIZE, 3*BOX_SIZE));
    circle.setTexture(circle_texture);
    cross.setTexture(cross_texture);
    board.setTexture(board_texture);
    board.setPosition(BOARD_ORIGIN_X,BOARD_ORIGIN_Y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                int x = sf::Mouse::getPosition(window).x;
                int y = sf::Mouse::getPosition(window).y;

                if(x >= BOARD_ORIGIN_X && x <= BOARD_ORIGIN_X + BOARD_WIDTH
                && y >= BOARD_ORIGIN_Y && y <= BOARD_ORIGIN_Y + BOARD_HEIGHT){
                    int i = (BOARD_ORIGIN_Y - y) / BOX_SIZE * (-1);
                    int h = (y - BOARD_ORIGIN_Y) / BOX_SIZE;
                    int j = (BOARD_ORIGIN_X - x) / BOX_SIZE * (-1);
                    std::cout << i << " ," << j <<std::endl;

                    if(field[i][j] == VOID){
                        //INSERT AND CHANGE TURN
                        field[i][j] = turn;
                        if(checkWin(field)){
                            if(turn == CROSS) std::cout<<"CROSS WIN!"<<std::endl;
                            else std::cout<<"CIRCLE WIN!"<<std::endl;
                        }
                        if(turn == CROSS) turn = CIRCLE;
                        else turn = CROSS;
                    }

                }
            }
        }

        window.clear(sf::Color::White);

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(field[i][j] == CROSS){
                    //DRAW CROSS
                    cross.setPosition(j * BOX_SIZE + BOARD_ORIGIN_X,i * BOX_SIZE + BOARD_ORIGIN_Y);
                    window.draw(cross);
                }
                else if(field[i][j] == CIRCLE){
                    //DRAW CIRCLE
                   circle.setPosition(j * BOX_SIZE + BOARD_ORIGIN_X,i * BOX_SIZE + BOARD_ORIGIN_Y);
                    window.draw(circle);
                }
            }
        }
        window.draw(board);
        window.display();
    }

    return 0;
}
bool checkWin(Turn field[][3])
{
    bool flag;
    Turn status_hor, status_ver;
    for(int i=0;i<3;i++){
        flag = true;
        status_hor = field[i][0];
        for(int j = 0;j<3;j++){
            if(field[i][j] == VOID || field[i][j]!= status_hor || status_hor == VOID){
                flag = false;
                break;
            }
        }
        if(flag) return true;

        flag = true;
        status_ver = field[0][i];
        for(int j = 0;j<3;j++){
            if(field[j][i] == VOID || field[j][i]!= status_ver || status_ver == VOID){
                flag = false;
                break;
            }
        }
        if(flag) return true;
    }


    flag = true;
    bool flag2 = true;
    status_hor = field[0][0];
    status_ver = field[2][0];
    for(int i = 1 ;i < 3 ;i++){
        if(field[i][i] != status_hor || field[i][i] == VOID){
            flag = false;
            status_hor = VOID;
        }

        if(field[2-i][i] != status_ver || field[2-i][i] == VOID){
            flag2 = false;
            status_ver = VOID;
        }
    }
    if(flag || flag2) return true;
    return false;
}



