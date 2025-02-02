#include<ncursesw/ncurses.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<locale.h>
#include<unistd.h>
#include<string.h>
#include<wchar.h>

//DEFINE
#define FOOD_NORMAL 0
#define FOOD_ELIXIR 1
#define FOOD_MAGIC 2
#define FOOD_ROTTEN 3

//STRUCT
typedef struct FOOD{
    char * name;
    int health_effect;
    int food_type;
    int timer;
}FOOD;

typedef struct GOLD{
    char * Name;
    int price_effect;
    int gold_type;
}GOLD;

typedef struct SPELL{
    char * namee;
    int spell_effect;
    int spell_type;
    int timer;
}SPELL;

typedef struct WEAPON{
    char * name;
    int weapon_effect;
    int weapon_type;
}WEAPON;

typedef struct ENEMY{
    char type;
    int health;
    int damage;
    int follow_steps;
    int x,y;
}ENEMY;

typedef struct LEVELs{
    char ** tiles;
    int level;
    int nrooms;
    struct ROOM ** rooms;
    struct Player * user;

}LEVELs;

typedef struct POSITION{
    int x;
    int y;
}POSITION;

typedef struct ROOM{
    POSITION position;
    FOOD ** foods;
    GOLD ** golds;
    SPELL ** spells;
    WEAPON ** weapons;
    ENEMY ** enemies;
    int nenemies;
    int nweapons;
    int nspells;
    int ngolds;
    int nfoods;
    int ntraps;
    int height;
    int width;
    int discoverd;
    POSITION ** DOOR;
}ROOM;

typedef struct Player{
    POSITION * position;
    int maxh;
    int score;
    int health;
    int power;
    int speed;
    int gold;
    int maxhealth;
}Player;


//GLOBALOB
int MAX_HEIGHT;
int MAX_WIDTH;
int timerepet=1;
int x=0;
char food_wehave[5]={' ',' ',' ',' ',' '};
char foodtype[5];
int spell_wehave_number[3]={0,0,0};
int weapon_wehave_number[6]={1,0,0,0,0,0};
int numfood=0;
int hunger=10;
int max_huger=10;
int backgroundcolorinfoodmenu=1;
int pas;
int spellmovment=0;
int hide_door_x=0;
int hide_door_y=0;
int discover_hide_door=0;
int hide_door_x1=0;
int hide_door_y1=0;
int discover_hide_door1=0;
int hide_door_x_2_1=0;
int hide_door_y_2_1=0;
int discover_hide_door_2_1=0;
int hide_door_x_2_2=0;
int hide_door_y_2_2=0;
int discover_hide_door_2_2=0;
int fast=0;
int weapon_wehave;
int whichroom=0;
int spellcounter=0;
int movement=0;
int spell=0;
int g=0;
int show_or_not=0;
int xweapon;


int Findroom[6];
int Drawroom[6];
int drawconnect_yes_or_no[6];
int Drawconnect[6];

//GLOBALFORSAVEMAP
int map[4][50][200];
int MAP[4][50][200];

//WEAPONGLOBAL
int p,x,r,v,t;
int pl,xl,rl,vl,tl;
//ENEMYGLOBAL
int D,T,P,X,W;

//TRAPCLOBAL
int trapplace[50][200];

//MAP&SCREEN&level
ROOM ** rooms_map();
void DRAWROOM(ROOM ** rooms);
ROOM ** smalldrawmap();
LEVELs * CREATELEVEL();
char ** LEVEL();
int screen();
int GAMELINE(LEVELs * level);
int ENDSCREEN(LEVELs * level);

//PLAYER
Player * playersetup();
POSITION * MOVE(int input,Player * user,LEVELs * level);
int PMOVE(POSITION * newP,Player * user,LEVELs* level);
int CHECK(POSITION * newP,LEVELs * level,FOOD * food,int ch);

//ROOM
ROOM * creatroom(int Tabel);
int drawROOM(ROOM * room,int Tabel);
int NightmareROOM(ROOM * room, int Tabel);
int SpellROOM(ROOM * room,int Tabel);
int TreasureROOM(ROOM * room,int Tabel);
int connectROOM(POSITION*DOOR1,POSITION*DOOR2);
int WHEREISPLAYER(ROOM ** rooms, Player * user);
ROOM * get_current_room(Player * user, LEVELs * level);
int get_room_number(Player * user,LEVELs * level);
void update_password_time();

//TRAP
void TRAP(ROOM * room,int R);

//FOOD
void PLACEFOODINROOM(ROOM * room);
void CONSUMEFOOD(Player * user,int num,LEVELs * level);
void DRAWFOOD(ROOM * room,int R);
void EINPUT(Player * user,LEVELs * level);
void draw_hunger_bar();
void update_hunger(LEVELs * level);

//GOLD
void PLACEFGOLDINROOM(ROOM * room);
void CONSUMEGOLD(Player * user,int num,LEVELs * level);
void DRAWGOLD(ROOM * room,int R);

//SPELL
void PLACESPELLINROOM(ROOM * room,int Tabel);
void CONSUMESPELL(Player * user,int num,LEVELs * level);
void DRAWSPELL(ROOM * room,int R);
void eINPUT(Player * user, LEVELs * level);

//WEAPON
void PLACEWEAPONINROOM(ROOM * room);
void DRAWWEAPON(ROOM * room,int R);
void iINPUT(Player * user, LEVELs * level);

//ENEMY
void PLACEENEMYINROOM(ROOM * room,int R);
void CONSUMEENEMY(Player * user,int num,LEVELs * level);
void DRAWENEMY(ROOM * room,int R);
void moveENEMY(Player * user, ENEMY * e);


//PATH
void ADDPositionxy(int ** front, int frontcounter, int y, int x);
int NEIGHBORS(int ** front,int frontcounter,int *** where, int y, int x);
void FIND(POSITION * start,POSITION * end);

//MAIN*************************************^54353
int mainprim(int t){
    // setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr,TRUE);
    nodelay(stdscr,TRUE);
    //Player * user;
    discover_hide_door=0;
    discover_hide_door1=0;
    discover_hide_door_2_1=0;
    discover_hide_door_2_2=0;
    
    for(int i=0;i<6;i++){
        Drawroom[i]=0;
        Findroom[i]=0;
        drawconnect_yes_or_no[i]=0;
        Drawconnect[i]=0;
    }
    Findroom[0]=1;
    Drawroom[0]=0;
    attron(COLOR_PAIR(2));
    attron(A_BOLD);
    mvprintw(31,0,"   ^_^ WELCOME TO FLOOR %d",t);
    attroff(COLOR_PAIR(2));
    attroff(A_BOLD);
    
    int ch;

    MAX_HEIGHT=25;
    MAX_WIDTH=100;

    POSITION * newP;
    LEVELs * level;
    FOOD * food;
    ENEMY * enemy;
    
    start_color();
    screen();
    level=CREATELEVEL(1);
    DRAWROOM(level->rooms);
    level->tiles=LEVEL();
    level->level=t;
    GAMELINE(level);
   // moveENEMY(level->user,enemy);
    scrollok(stdscr, TRUE);

    if(level->level==1){
        init_pair(2,COLOR_GREEN,COLOR_BLACK);
        attron(COLOR_PAIR(2));
    }
    if(level->level==2){
        init_pair(1,COLOR_MAGENTA,COLOR_BLACK);
        attron(COLOR_PAIR(1));
    }
    if(level->level==3){
        init_pair(100,COLOR_CYAN,COLOR_BLACK);
        attron(COLOR_PAIR(100));
    }
    if(level->level==4){
        init_pair(101,COLOR_YELLOW,COLOR_BLACK);
        attron(COLOR_PAIR(101));
    }
        mvprintw(5,110,"              a          a");
        mvprintw(6,110,"            aaa        aaa");
        mvprintw(7,110,"           aaaaaaaaaaaaaaaa");
        mvprintw(8,110,"          aaaaaaaaaaaaaaaaaa");
        mvprintw(9,110,"         aaaaaUaaaaaaaUaaaaaa");
        mvprintw(10,110,"         aaaaaaaaaaaaaaaaaaa");
        mvprintw(11,110,"          aaaaaaaaaaaaaaaaaa");
        mvprintw(12,110,"           aaaaaaa  aaaaaaa");
        mvprintw(13,110,"            aaaaaaaaaaaaaa");
        mvprintw(14,110," a         aaaaaaaaaaaaaaaa");
        mvprintw(15,110,"aaa       aaaaaaaaaaaaaaaaaa");
        mvprintw(16,110,"aaa      aaaaaaaaaaaaaaaaaaaa");
        mvprintw(17,110,"aaa     aaaaaaaaaaaaaaaaaaaaaa");
        mvprintw(18,110,"aaa    aaaaaaaaaaaaaaaaaaaaaaaa");
        mvprintw(19,110," aaa   aaaaaaaaaaaaaaaaaaaaaaaa");
        mvprintw(20,110," aaa   aaaaaaaaaaaaaaaaaaaaaaaa");
        mvprintw(21,110," aaa    aaaaaaaaaaaaaaaaaaaaaa");
        mvprintw(22,110,"  aaa    aaaaaaaaaaaaaaaaaaaa");
        mvprintw(23,110,"   aaaaaaaaaaaaaaaaaaaaaaaaaa");
        mvprintw(24,110,"    aaaaaaaaaaaaaaaaaaaaaaaaa");
    if(level->level==1){
        attroff(COLOR_PAIR(2));
    }
    if(level->level==2){
        attroff(COLOR_PAIR(1));
    }
    if(level->level==3){
        attroff(COLOR_PAIR(100));
    }
    if(level->level==4){
        attroff(COLOR_PAIR(101));
    }
    while((ch=getch())!='q'){
        //GAMELINE(level);
        update_hunger(level);
        newP=MOVE(ch, level->user,level);
        int back=CHECK(newP,level,food,ch);
        move(level->user->position->y,level->user->position->x);

    }
    
    endwin();
    return 0;
}
int main(){
    initscr();
    setlocale(LC_ALL, "");
    mainprim(timerepet);
    return 0;
}

//SCREEN
int screen(){
    setlocale(LC_ALL, "");
    initscr();
    // setlocale(LC_ALL, "");
    start_color();
    srand(time(NULL));
    noecho();
    cbreak;
    refresh();
    return 1;
}
int GAMELINE(LEVELs * level){
    start_color();
    init_pair(5,COLOR_CYAN,COLOR_BLACK);
    attron(COLOR_PAIR(5));
    attron(A_BOLD);
    mvprintw(30,0,"   Level: %d/4",level->level);
    printw("    Gold: %d",level->user->gold);
    printw("    Health:%d",level->user->health);
    printw("    Hit: %d",level->user->power);
    printw("    Score: %d",level->user->score);
    printw("    Speed: %d",level->user->speed);
    attroff(A_BOLD);
    attroff(COLOR_PAIR(5));

    return 1;
}
int ENDSCREEN(LEVELs * level){
    curs_set(0);
    clear();
    refresh();
    init_pair(34,COLOR_BLACK,COLOR_GREEN);
    attron(COLOR_PAIR(34));
    attron(A_BOLD);
    attron(A_BLINK);
    mvprintw(15,15,"^_^");
    attroff(A_BLINK);
    mvprintw(15,18,"Congratulations on completing Rogue!                                                    ");
    attroff(A_BOLD);
    mvprintw(16,18,"You have navigated through all the twists and turns, overcoming every challenge and     ");
    mvprintw(17,18,"obstacle in your path. Your determination, strategy, and skill have truly shone through.");
    mvprintw(18,18,"This achievement is a reflection of your hard work and dedication.                      ");
    mvprintw(19,18,"                                                                                        ");
    attron(A_BOLD);
    mvprintw(20,18,"Well done, and here is to many more epic quests and victories ahead!!                   ");
    attroff(A_BOLD);

    init_pair(35,COLOR_BLACK,COLOR_CYAN);
    attron(COLOR_PAIR(35));
    attron(A_ITALIC);
    mvprintw(22,18,"    YOUR SCORE %d                                                                       ",level->user->score);

    attroff(COLOR_PAIR(35));
    attroff(A_ITALIC);

    move(30,0);
    clrtoeol();
    return 1;
}

//MAP
LEVELs * CREATELEVEL(int level){
    LEVELs * newlevel;
    newlevel=malloc(sizeof(LEVELs));
    newlevel->level = level;
    newlevel->nrooms=6;
    newlevel->rooms=rooms_map();
    
    newlevel->tiles=LEVEL();
    newlevel->user=playersetup();
    WHEREISPLAYER(newlevel->rooms, newlevel->user);
    return newlevel;
}

ROOM ** rooms_map(){

    int x;
    
    ROOM ** rooms;
    rooms=malloc(sizeof(ROOM*)*6);
    
    for (int i=0;i<6;i++){
        rooms[i]=creatroom(i);
    }
   return rooms;
}

void DRAWROOM(ROOM ** rooms){
     if(Findroom[1]==1 && Drawroom[1]==0){
        spell=3;
        SpellROOM(rooms[1],1);
        Drawroom[1]=1;
    }
    else if( Findroom[4]==1 && Drawroom[4]==0){
        spell=2;
        SpellROOM(rooms[4],4);
        Drawroom[4]=1;
    }
    else if(Findroom[2]==1 && Drawroom[2]==0){
        spell=1;
        NightmareROOM(rooms[2],2);
        Drawroom[2]=1;
    }
    else if(Findroom[3]==1 && timerepet==4 && Drawroom[3]==0){
        spell=1;
        TreasureROOM(rooms[3],3);
        Drawroom[3]=1;
    }
    else if(Findroom[3]==1 && Drawroom[3]==0){
        spell=1;
        drawROOM(rooms[3],3);
        Drawroom[3]=1;
    }
    else if(Findroom[0]==1 && Drawroom[0]==0){
        spell=1;
        drawROOM(rooms[0],0);
        Drawroom[0]=1;
    }
    else if(Findroom[5]==1 && Drawroom[5]==0){
        spell=1;
        drawROOM(rooms[5],5);
        Drawroom[5]=1;
    }

    if(drawconnect_yes_or_no[0]==1 && Drawconnect[0]==0){
        connectROOM(rooms[0]->DOOR[1],rooms[3]->DOOR[0]);
        Drawconnect[0]=1;
    }
    if(drawconnect_yes_or_no[1]==1 && Drawconnect[1]==0){
        connectROOM(rooms[3]->DOOR[3],rooms[4]->DOOR[2]);
        Drawconnect[1]=1;
    }
    if(drawconnect_yes_or_no[2]==1 && Drawconnect[2]==0){
        connectROOM(rooms[4]->DOOR[3],rooms[5]->DOOR[2]);
        Drawconnect[2]=1;
    }
    if(drawconnect_yes_or_no[3]==1 && Drawconnect[3]==0){
        connectROOM(rooms[5]->DOOR[0],rooms[2]->DOOR[1]);
        Drawconnect[3]=1;
    }
    if(drawconnect_yes_or_no[4]==1 && Drawconnect[4]==0){
        connectROOM(rooms[2]->DOOR[2],rooms[1]->DOOR[3]);
        Drawconnect[4]=1;
    }
    if(drawconnect_yes_or_no[5]==1 && Drawconnect[5]==0){
        connectROOM(rooms[0]->DOOR[3],rooms[1]->DOOR[2]);
        Drawconnect[5]=1;
    }
}

char ** LEVEL(){
    int XXX=0;
    int YYY=0;
    char ** position;
    position=malloc(sizeof(char *)*MAX_HEIGHT);

    for(YYY=0;YYY<MAX_HEIGHT;YYY++){
        position[YYY]=malloc(sizeof(char)*MAX_WIDTH);
        for(XXX=0;XXX<MAX_WIDTH;XXX++){
            position[YYY][XXX]=mvinch(YYY,XXX);
        }
    }
    return position;
}

//ROOM
ROOM * creatroom(int Tabel){
        ROOM * newROOM;
        newROOM=malloc(sizeof(ROOM));
        
        switch(Tabel){
            case 0:
                newROOM->position.x=0;
                newROOM->position.y=0;

                break;
            case 1:
                newROOM->position.x=33;
                newROOM->position.y=0;
                break;
            case 2:
                newROOM->position.x=66;
                newROOM->position.y=0;
                break;
            case 3:
                newROOM->position.x=0;
                newROOM->position.y=15;
                break;
            case 4:
                newROOM->position.x=33;
                newROOM->position.y=15;
                break;
            case 5:
                newROOM->position.x=66;
                newROOM->position.y=15;
                break;
        
        }

        newROOM->discoverd=1;
        newROOM->height=rand() % 6 + 6;//12
        newROOM->width=rand() % 6+ 10;//12

        if(Tabel==3 || Tabel==4){
            newROOM->height=rand()%3+4;
            newROOM->width=rand()%6+10;
        }
        if(Tabel==5){
            newROOM->height=rand()%3+4;
            newROOM->width=rand()%6+10;
        }
        
        newROOM->position.x += rand() % (13-newROOM->height + 1);
        newROOM->position.y += rand() % 3;
        
        
        newROOM->DOOR=malloc(sizeof(POSITION)*4);//2

        newROOM->DOOR[0]=malloc(sizeof(POSITION));
        newROOM->DOOR[0]->x=rand()%(newROOM->width-2)+newROOM->position.x+1;
        newROOM->DOOR[0]->y=newROOM->position.y;

        newROOM->DOOR[1]=malloc(sizeof(POSITION));
        newROOM->DOOR[1]->x=rand()%(newROOM->width-2)+newROOM->position.x+1;
        newROOM->DOOR[1]->y=newROOM->position.y+newROOM->height;

        newROOM->DOOR[2]=malloc(sizeof(POSITION));
        newROOM->DOOR[2]->y=rand()%(newROOM->height-2)+newROOM->position.y+1;
        newROOM->DOOR[2]->x=newROOM->position.x;

        newROOM->DOOR[3]=malloc(sizeof(POSITION));
        newROOM->DOOR[3]->y=rand()%(newROOM->height-2)+newROOM->position.y+1;
        newROOM->DOOR[3]->x=newROOM->position.x+newROOM->width-1;


        return newROOM;
}

int drawROOM(ROOM * room,int Tabel){
    
    int x;
    int y;
    int R;
        //top
        for(x=room->position.x;x<room->position.x+room->width;x++){
            start_color();
            init_pair(2,COLOR_GREEN,COLOR_BLACK);
            attron(COLOR_PAIR(2));
            mvprintw(room->position.y, x,"-");
            attroff(COLOR_PAIR(2));
            map[0][room->position.y][x]=2;
        }
        mvprintw(room->position.y,room->position.x+2,"=");
        map[0][room->position.y][room->position.x+2]=7;
        //bottom
        for(x=room->position.x;x<room->position.x+room->width;x++){
            start_color();
            init_pair(2,COLOR_GREEN,COLOR_BLACK);
            attron(COLOR_PAIR(2));
            mvprintw(room->position.y+room->height, x,"-");
            attroff(COLOR_PAIR(2));
            map[0][room->position.y+room->height][x]=2;
        }
        //right
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            start_color();
            init_pair(2,COLOR_GREEN,COLOR_BLACK);
            attron(COLOR_PAIR(2));
            mvprintw(y,room->position.x,"|");
            attroff(COLOR_PAIR(2));
            map[0][y][room->position.x]=3;
        }
        //left
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            start_color();
            init_pair(2,COLOR_GREEN,COLOR_BLACK);
            attron(COLOR_PAIR(2));
            mvprintw(y,room->position.x+room->width-1,"|");
            attroff(COLOR_PAIR(2));
            map[0][y][room->position.x+room->width-1]=3;
        }
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            for(x=room->position.x+1;x<room->position.x+room->width-1;x++){
                mvprintw(y,x,".");
                map[0][y][x]=1;
            }
            start_color();
            init_pair(3,COLOR_MAGENTA,COLOR_BLACK);
            attron(COLOR_PAIR(3));
            mvprintw(room->position.y+2,room->position.x+2,"o");
            attroff(COLOR_PAIR(3));
            map[0][room->position.y+2][room->position.x+2]=5;
            
        }
        PLACEFOODINROOM(room);
        DRAWFOOD(room,0);
        PLACEFGOLDINROOM(room);
        DRAWGOLD(room,0);
        PLACESPELLINROOM(room,Tabel);
        DRAWSPELL(room,0);
        PLACEWEAPONINROOM(room);
        DRAWWEAPON(room,0);
        switch(Tabel){
            case 0:
                R=0;
                break;
            case 3:
                R=3;
                break;
            case 5:
                R=5;
                break;
        }
        PLACEENEMYINROOM(room,R);
        DRAWENEMY(room,0);
        
        TRAP(room,0);
        switch(Tabel){
            case 0:
                mvprintw(room->DOOR[1]->y,room->DOOR[1]->x,"+");
                mvprintw(room->DOOR[3]->y,room->DOOR[3]->x,"+");
                mvprintw((room->DOOR[1]->y+room->DOOR[3]->y)/2,(room->DOOR[1]->x+room->DOOR[3]->x)/2,"<");
                map[0][room->DOOR[1]->y][room->DOOR[1]->x]=8;
                map[0][room->DOOR[3]->y][room->DOOR[3]->x]=8;
                //map[(room->DOOR[1]->y+room->DOOR[3]->y)/2][(room->DOOR[1]->x+room->DOOR[3]->x)/2]=9;
                break;
            case 1:
                mvprintw(room->DOOR[2]->y,room->DOOR[2]->x,"+");
                map[0][room->DOOR[2]->y][room->DOOR[2]->x]=8;
                start_color();
                init_pair(2,COLOR_GREEN,COLOR_BLACK);
                attron(COLOR_PAIR(2));
                mvprintw(room->DOOR[3]->y,room->DOOR[3]->x,"|");
                map[0][room->DOOR[3]->y][room->DOOR[3]->x]=3;
                mvprintw(room->DOOR[3]->y+1,room->DOOR[3]->x,"|");
                map[0][room->DOOR[3]->y+1][room->DOOR[3]->x]=3;
                mvprintw(room->DOOR[3]->y-1,room->DOOR[3]->x,"|");
                map[0][room->DOOR[3]->y-1][room->DOOR[3]->x]=3;
                attroff(COLOR_PAIR(2));
                hide_door_x=room->DOOR[3]->x;
                hide_door_y=room->DOOR[3]->y;
                if(timerepet==1){
                 mvprintw((room->DOOR[2]->y+room->DOOR[3]->y)/2,(room->DOOR[2]->x+room->DOOR[3]->x)/2,">");
                 map[0][(room->DOOR[2]->y+room->DOOR[3]->y)/2][(room->DOOR[2]->x+room->DOOR[3]->x)/2]=9;
                }

                break;
            case 2:
                mvprintw(room->DOOR[1]->y,room->DOOR[1]->x,"+");
                map[0][room->DOOR[1]->y][room->DOOR[1]->x]=8;
                mvprintw(room->DOOR[2]->y,room->DOOR[2]->x,"+");
                map[0][room->DOOR[2]->y][room->DOOR[2]->x]=8;
                break;
            case 3:
                mvprintw(room->DOOR[0]->y,room->DOOR[0]->x,"+");
                map[0][room->DOOR[0]->y][room->DOOR[0]->x]=8;
                mvprintw(room->DOOR[3]->y,room->DOOR[3]->x,"+");
                map[0][room->DOOR[3]->y][room->DOOR[3]->x]=8;
                if(timerepet==2){
                    mvprintw((room->DOOR[0]->y+room->DOOR[3]->y)/2,(room->DOOR[0]->x+room->DOOR[3]->x)/2,">");
                    map[0][(room->DOOR[0]->y+room->DOOR[3]->y)/2][(room->DOOR[0]->x+room->DOOR[3]->x)/2]=9;
                }
                break;
            case 4:
                mvprintw(room->DOOR[2]->y,room->DOOR[2]->x,"+");
                map[0][room->DOOR[2]->y][room->DOOR[2]->x]=8;
                mvprintw(room->DOOR[3]->y,room->DOOR[3]->x,"+");
                map[0][room->DOOR[3]->y][room->DOOR[3]->x]=8;
                if(timerepet==3){
                 mvprintw((room->DOOR[2]->y+room->DOOR[3]->y)/2,(room->DOOR[2]->x+room->DOOR[3]->x)/2,">");
                 map[0][(room->DOOR[2]->y+room->DOOR[3]->y)/2][(room->DOOR[2]->x+room->DOOR[3]->x)/2]=9;
                }
                break;
            case 5:
                mvprintw(room->DOOR[0]->y,room->DOOR[0]->x,"+");
                map[0][room->DOOR[0]->y][room->DOOR[0]->x]=8;
                mvprintw(room->DOOR[2]->y,room->DOOR[2]->x,"+");
                map[0][room->DOOR[2]->y][room->DOOR[2]->x]=8;
                 if(timerepet==4){
                 mvprintw((room->DOOR[0]->y+room->DOOR[2]->y)/2,(room->DOOR[0]->x+room->DOOR[2]->x)/2,">");
                 map[0][(room->DOOR[0]->y+room->DOOR[2]->y)/2][(room->DOOR[0]->x+room->DOOR[2]->x)/2]=9;
                }
                break;
        
        }
        
        


    return 1;
}

int NightmareROOM(ROOM * room, int Tabel){
    int x;
    int y;
        //top
        for(x=room->position.x;x<room->position.x+room->width;x++){
            start_color();
            init_pair(10,COLOR_BLUE,COLOR_BLACK);
            attron(COLOR_PAIR(10));
            mvprintw(room->position.y, x,"-");
            attroff(COLOR_PAIR(10));
            map[1][room->position.y][x]=2;
        }
        //bottom
        for(x=room->position.x;x<room->position.x+room->width;x++){
            start_color();
            init_pair(10,COLOR_BLUE,COLOR_BLACK);
            attron(COLOR_PAIR(10));
            mvprintw(room->position.y+room->height, x,"-");
            attroff(COLOR_PAIR(10));
            map[1][room->position.y+room->height][x]=2;
        }
        //right
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            start_color();
            init_pair(10,COLOR_BLUE,COLOR_BLACK);
            attron(COLOR_PAIR(10));
            mvprintw(y,room->position.x,"|");
            attroff(COLOR_PAIR(10));
            map[1][y][room->position.x]=3;
        }
        //left
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            start_color();
            init_pair(10,COLOR_BLUE,COLOR_BLACK);
            attron(COLOR_PAIR(10));
            mvprintw(y,room->position.x+room->width-1,"|");
            attroff(COLOR_PAIR(10));
            map[1][y][room->position.x+room->width-1]=3;
        }
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            for(x=room->position.x+1;x<room->position.x+room->width-1;x++){
                mvprintw(y,x,".");
                map[1][y][x]=1;
            }
            
        }
        init_pair(13,COLOR_RED,COLOR_WHITE);
        attron(COLOR_PAIR(13));
        mvprintw(room->DOOR[1]->y,room->DOOR[1]->x+1,"@");
        map[1][room->DOOR[1]->y][room->DOOR[1]->x+1]=4;
        attroff(COLOR_PAIR(13));
        mvprintw(room->DOOR[2]->y,room->DOOR[2]->x,"+");
        map[1][room->DOOR[2]->y][room->DOOR[2]->x]=8;

        mvprintw(room->position.y+1,room->position.x+1,"&");
        map[1][room->position.y+1][room->position.x+1]=6;
        
        int X=room->position.x+rand()%(room->width-2)+2;
        int Y=room->position.y+rand()%(room->height-2)+2;
        int xkocholo=room->position.x+rand()%(room->width-2)+2;
        int ykocholo=room->position.y+rand()%(room->height-2)+2;
        int xstoon=room->position.x+rand()%(room->width-2)+2;
        int ystoon=room->position.y+rand()%(room->height-2)+2;
        init_pair(11,COLOR_BLUE,COLOR_WHITE);
        attron(COLOR_PAIR(11));
        mvprintw(Y,X,"s");
        map[1][Y][X]=12;
        mvprintw(ykocholo,xkocholo,"g");
        map[1][ykocholo][xkocholo]=11;
        attroff(COLOR_PAIR(11));
        init_pair(12,COLOR_MAGENTA,COLOR_WHITE);
        attron(COLOR_PAIR(12));
        mvprintw(ystoon,xstoon,"o");
        map[1][ystoon][xstoon]=5;
        attroff(COLOR_PAIR(12));
        
    return 1;
}

int SpellROOM(ROOM * room,int Tabel){
    int x;
    int y;
   // start_color();
    init_pair(30,COLOR_MAGENTA,COLOR_BLACK);
        //top
        for(x=room->position.x;x<room->position.x+room->width;x++){
            
            attron(COLOR_PAIR(30));
            mvprintw(room->position.y, x,"-");
            map[2][room->position.y][x]=2;
            attroff(COLOR_PAIR(30));

        }
        //bottom
        for(x=room->position.x;x<room->position.x+room->width;x++){
            attron(COLOR_PAIR(30));
            mvprintw(room->position.y+room->height, x,"-");
            map[2][room->position.y+room->height][x]=2;
            attroff(COLOR_PAIR(30));
        }
        //right
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
    
            attron(COLOR_PAIR(30));
            mvprintw(y,room->position.x,"|");
            map[2][y][room->position.x]=3;
            attroff(COLOR_PAIR(30));
        }
        //left
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            attron(COLOR_PAIR(30));
            mvprintw(y,room->position.x+room->width-1,"|");
            map[2][y][room->position.x+room->width-1]=3;
            attroff(COLOR_PAIR(30));
        }
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            for(x=room->position.x+1;x<room->position.x+room->width-1;x++){
                mvprintw(y,x,".");
                map[2][y][x]=1;
            }
            
        }
        
        switch(Tabel){
            case 1:
                attron(COLOR_PAIR(30));
                mvprintw(room->DOOR[2]->y,room->DOOR[2]->x,"|");
                map[2][room->DOOR[2]->y][room->DOOR[2]->x]=13;
                mvprintw(room->DOOR[2]->y+1,room->DOOR[2]->x,"|");
                map[2][room->DOOR[2]->y+1][room->DOOR[2]->x]=3;
                mvprintw(room->DOOR[2]->y-1,room->DOOR[2]->x,"|");
                map[2][room->DOOR[2]->y-1][room->DOOR[2]->x]=3;
                hide_door_x=room->DOOR[2]->x;
                hide_door_y=room->DOOR[2]->y;
                mvprintw(room->DOOR[3]->y,room->DOOR[3]->x,"|");
                map[2][room->DOOR[3]->y][room->DOOR[3]->x]=13;
                mvprintw(room->DOOR[3]->y+1,room->DOOR[3]->x,"|");
                map[2][room->DOOR[3]->y+1][room->DOOR[3]->x]=3;
                mvprintw(room->DOOR[3]->y-1,room->DOOR[3]->x,"|");
                map[2][room->DOOR[3]->y-1][room->DOOR[3]->x]=3;
                attroff(COLOR_PAIR(30));
                hide_door_x1=room->DOOR[3]->x;
                hide_door_y1=room->DOOR[3]->y;
                if(timerepet==1){
                 mvprintw((room->DOOR[2]->y+room->DOOR[3]->y)/2,(room->DOOR[2]->x+room->DOOR[3]->x)/2,">");
                 map[2][(room->DOOR[2]->y+room->DOOR[3]->y)/2][(room->DOOR[2]->x+room->DOOR[3]->x)/2]=9;
                }
                break;
            case 4:
                attron(COLOR_PAIR(30));
                mvprintw(room->DOOR[2]->y,room->DOOR[2]->x,"|");
                map[2][room->DOOR[2]->y][room->DOOR[2]->x]=3;
                mvprintw(room->DOOR[2]->y+1,room->DOOR[2]->x,"|");
                map[2][room->DOOR[2]->y+1][room->DOOR[2]->x]=3;
                mvprintw(room->DOOR[2]->y-1,room->DOOR[2]->x,"|");
                map[2][room->DOOR[2]->y-1][room->DOOR[2]->x]=3;
                hide_door_x_2_1=room->DOOR[2]->x;
                hide_door_y_2_1=room->DOOR[2]->y;
                mvprintw(room->DOOR[3]->y,room->DOOR[3]->x,"|");
                map[2][room->DOOR[3]->y][room->DOOR[3]->x]=3;
                mvprintw(room->DOOR[3]->y+1,room->DOOR[3]->x,"|");
                map[2][room->DOOR[3]->y+1][room->DOOR[3]->x]=3;
                mvprintw(room->DOOR[3]->y-1,room->DOOR[3]->x,"|");
                map[2][room->DOOR[3]->y-1][room->DOOR[3]->x]=3;
                hide_door_x_2_2=room->DOOR[3]->x;
                hide_door_y_2_2=room->DOOR[3]->y;
                if(timerepet==3){
                 mvprintw((room->DOOR[2]->y+room->DOOR[3]->y)/2,(room->DOOR[2]->x+room->DOOR[3]->x)/2,">");
                 map[2][(room->DOOR[2]->y+room->DOOR[3]->y)/2][(room->DOOR[2]->x+room->DOOR[3]->x)/2]=9;
                }
                break;
        }
        PLACESPELLINROOM(room,Tabel);
        DRAWSPELL(room,2);
        if(Tabel==1){
            mvprintw((room->DOOR[2]->y+room->DOOR[3]->y)/2,(room->DOOR[2]->x+room->DOOR[3]->x)/2,">");
            map[2][(room->DOOR[2]->y+room->DOOR[3]->y)/2][(room->DOOR[2]->x+room->DOOR[3]->x)/2]=9;
        }
    return 1;
}

int TreasureROOM(ROOM * room,int Tabel){
    int x;
    int y;
        //top
        for(x=room->position.x;x<room->position.x+room->width;x++){
            start_color();
            init_pair(33,COLOR_YELLOW,COLOR_BLACK);
            attron(COLOR_PAIR(33));
            mvprintw(room->position.y, x,"-");
            map[3][room->position.y][x]=2;
            attroff(COLOR_PAIR(33));

        }
        //bottom
        for(x=room->position.x;x<room->position.x+room->width;x++){
            attron(COLOR_PAIR(33));
            mvprintw(room->position.y+room->height, x,"-");
            map[3][room->position.y+room->height][x]=2;
            attroff(COLOR_PAIR(33));
        }
        //right
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            attron(COLOR_PAIR(33));
            mvprintw(y,room->position.x,"|");
            map[3][y][room->position.x]=3;
            attroff(COLOR_PAIR(33));
        }
        //left
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            attron(COLOR_PAIR(33));
            mvprintw(y,room->position.x+room->width-1,"|");
            map[3][y][room->position.x+room->width-1]=3;
            attroff(COLOR_PAIR(33));
        }
        for(y=room->position.y+1;y<room->position.y+room->height;y++){
            for(x=room->position.x+1;x<room->position.x+room->width-1;x++){
                mvprintw(y,x,".");
                map[3][y][x]=1;
            }
            
        }
        
        mvprintw(room->DOOR[0]->y,room->DOOR[0]->x,"+");
        map[3][room->DOOR[0]->y][room->DOOR[0]->x]=8;
        mvprintw(room->DOOR[3]->y,room->DOOR[3]->x,"+");
        map[3][room->DOOR[3]->y][room->DOOR[3]->x]=8;

        PLACEFGOLDINROOM(room);
        DRAWGOLD(room,3);

        init_pair(36,COLOR_YELLOW,COLOR_BLACK);
        attron(A_BOLD);
        attron(COLOR_PAIR(36));
        mvprintw((room->DOOR[0]->y+room->DOOR[3]->y)/2,(room->DOOR[0]->x+room->DOOR[3]->x)/2,"O");
        map[3][(room->DOOR[0]->y+room->DOOR[3]->y)/2][(room->DOOR[0]->x+room->DOOR[3]->x)/2]=10;
        attroff(A_BOLD);
        attroff(COLOR_PAIR(36));

        TRAP(room,3);
        
        
    return 1;
}

//#CONNECTDOORS
int connectROOM(POSITION*DOOR1,POSITION*DOOR2){
   
    int dx=abs(DOOR2->x - DOOR1->x);
    int dy=abs(DOOR2->y - DOOR1->y);
    int sx=(DOOR1->x < DOOR2->x)? 1 : -1;
    int sy=(DOOR1->y < DOOR2->y) ? 1 : -1;
    int err= dx - dy;
    mvaddch(DOOR1->y,DOOR1->x,'+');
    while((DOOR1->x != DOOR2->x)||(DOOR1->y != DOOR2->y)){
        int e=2*err;
        if(e>-dy){
            err-=dy;
            DOOR1->x +=sx;
        }
        else if(e<dx){
            err+=dx;
            DOOR1->y += sy;
        }

        if((DOOR1->x == DOOR2->x)&&(DOOR1->y == DOOR2->y)){
           // mvaddch(DOOR1->y,DOOR1->x,'+');
        }
        else{
            if((mvinch(DOOR1->y,DOOR1->x)=='|') || (mvinch(DOOR1->y,DOOR1->x)=='-')){
                break;
            }
            else{
                mvaddch(DOOR1->y,DOOR1->x,'#');
                map[0][DOOR1->y][DOOR1->x]=15;
            }
        }
    }

    return 1;
}

//PALYER
Player * playersetup(){
        Player * newPlayer;
        newPlayer=malloc(sizeof(Player));

        newPlayer->position=malloc(sizeof(POSITION));

    
        newPlayer->health=40;
        newPlayer->gold=0;
        newPlayer->score=0;
        newPlayer->maxh=20;//30
        newPlayer->power=0;

        // mvprintw(newPlayer->position->y,newPlayer->position->x,"$");
        // move(newPlayer->position->y,newPlayer->position->x);


        return newPlayer;

}

int WHEREISPLAYER(ROOM ** rooms, Player * user){
    user->position->x= rooms[0]->position.x+1;
    user->position->y= rooms[0]->position.y+1;

    //getch();
   mvprintw(user->position->y,user->position->x,"$");
    //mvinstr(user->position->y,user->position->x,"\u263B");
    // mvaddch(user->position->y,user->position->x,"\u263B");
    move(user->position->y,user->position->x);
    
}
ROOM * get_current_room(Player * user, LEVELs * level){
    for(int i=0;i<level->nrooms;i++){
        ROOM * room=level->rooms[i];

        if((user->position->x >= room->position.x)&&(user->position->x < room->position.x + room->width)&&(user->position->y >=room->position.y)&&(user->position->y < room->position.y + room->height)){
            return room;
        }
    }
    return NULL;
}
int get_room_number(Player * user,LEVELs * level){
    for(int i=0;i<level->nrooms;i++){
        ROOM * room=level->rooms[i];

        if((user->position->x >= room->position.x)&&(user->position->x < room->position.x + room->width)&&(user->position->y>= room->position.y)&&(user->position->y < room->position.y+room->height)){
            return i;
        }
    }
    return -1;
}
POSITION * MOVE(int input,Player * user,LEVELs * level){
    int findroomprim[6]={0};
    int dra[6]={0};
    int drawroomprim[6]={0};
    POSITION * newP;
    if(movement==0){
        user->speed=0;
    }
    newP=malloc(sizeof(POSITION));
    
        switch(input){
        case 'J':
        case 'j':
            movement--;
            if(fast){
                int iii=0;
                int one=1;
                while(one){
                    switch(mvinch(user->position->y-iii-1,user->position->x)){
                    case '.':
                        iii++;
                        break;
                    default:
                        one=0;
                        break;
                    }
                }
                newP->y=user->position->y-iii;
                newP->x=user->position->x;
                fast=0;
                break;
            }
            else if(user->speed>=2){
                newP->y=user->position->y-2;
                newP->x=user->position->x;
            }
            else{
                newP->y=user->position->y-1;
                newP->x=user->position->x;
                break;
            }
            break;
        case 'Y':
        case 'y':
            movement--;
            if(fast){
                int iii=0;
                int one=1;
                while(one){
                    switch(mvinch(user->position->y-iii-1,user->position->x-1-iii)){
                    case '.':
                        iii++;
                        break;
                    default:
                        one=0;
                        break;
                    }
                }
                newP->y=user->position->y-iii;
                newP->x=user->position->x-iii;
                fast=0;
                break;
            }
            else if(user->speed>=2){
                newP->y=user->position->y-2;
                newP->x=user->position->x-2;
            }
            else{
                newP->y=user->position->y-1;
                newP->x=user->position->x-1;
                break;
            } 
            break;
        case 'U':
        case 'u':
            movement--;
            if(fast){
                int iii=0;
                int one=1;
                while(one){
                    switch(mvinch(user->position->y-iii-1,user->position->x+1+iii)){
                    case '.':
                        iii++;
                        break;
                    default:
                        one=0;
                        break;
                    }
                }
                newP->y=user->position->y-iii;
                newP->x=user->position->x+iii;
                fast=0;
                break;
            }
            else if(user->speed>=2){
                newP->y=user->position->y-2;
                newP->x=user->position->x+2;
            }
            else{
                newP->y=user->position->y-1;
                newP->x=user->position->x+1;
                break;
            }
            break;
        case 'H':
        case 'h':
            movement--;
            if(fast){
                int iii=0;
                int one=1;
                while(one){
                    switch(mvinch(user->position->y,user->position->x-1-iii)){
                    case '.':
                        iii++;
                        break;
                    default:
                        one=0;
                        break;
                    }
                }
                newP->y=user->position->y;
                newP->x=user->position->x-iii;
                fast=0;
                break;
            }
            else if(user->speed>=2){
                newP->y=user->position->y;
                newP->x=user->position->x-2;
            }
            else{
                newP->y=user->position->y;
                newP->x=user->position->x-1;
                break;
            }
            break;
        case 'L':
        case 'l':
            movement--;
            if(fast){
                int iii=0;
                int one=1;
                while(one){
                    switch(mvinch(user->position->y,user->position->x+1+iii)){
                    case '.':
                        iii++;
                        break;
                    default:
                        one=0;
                        break;
                    }
                }
                newP->y=user->position->y;
                newP->x=user->position->x+iii;
                fast=0;
                break;
            }
            else if(user->speed>=2){
                newP->y=user->position->y;
                newP->x=user->position->x+2;
            }
            else{
                newP->y=user->position->y;
                newP->x=user->position->x+1;
                break;
            }
            break;
        case 'K':
        case 'k':
            movement--;
            if(fast){
                int iii=0;
                int one=1;
                while(one){
                    switch(mvinch(user->position->y+1+iii,user->position->x)){
                    case '.':
                        iii++;
                        break;
                    default:
                        one=0;
                        break;
                    }
                }
                newP->y=user->position->y+iii;
                newP->x=user->position->x;
                fast=0;
                break;
            }
            else if(user->speed>=2){
                newP->y=user->position->y+2;
                newP->x=user->position->x;
            }
            else{
                newP->y=user->position->y+1;
                newP->x=user->position->x;
                break;
            } 
            break;
        case 'B':
        case 'b':
            movement--;
            if(fast){
                int iii=0;
                int one=1;
                while(one){
                    switch(mvinch(user->position->y+1+iii,user->position->x-1-iii)){
                    case '.':
                        iii++;
                        break;
                    default:
                        one=0;
                        break;
                    }
                }
                newP->y=user->position->y+iii;
                newP->x=user->position->x-iii;
                fast=0;
                break;
            }
            else if(user->speed>=2){
                newP->y=user->position->y+2;
                newP->x=user->position->x-2;
            }
            else{
                newP->y=user->position->y+1;
                newP->x=user->position->x-1;
                break;
            } 
            break;
        case 'N':
        case 'n':
            movement--;
            if(fast){
                int iii=0;
                int one=1;
                while(one){
                    switch(mvinch(user->position->y+1+iii,user->position->x+1+iii)){
                    case '.':
                        iii++;
                        break;
                    default:
                        one=0;
                        break;
                    }
                }
                newP->y=user->position->y+iii;
                newP->x=user->position->x+iii;
                fast=0;
                break;
            }
            else if(user->speed>=2){
                newP->y=user->position->y+2;
                newP->x=user->position->x+2;
            }
            else{
                newP->y=user->position->y+1;
                newP->x=user->position->x+1;
                break;
            } 
            break;
        case 'E':
            backgroundcolorinfoodmenu=1;
            EINPUT(user,level);
            break;
        case '/':
            if((numfood<5)){
                switch(mvinch(user->position->y,user->position->x+1) &A_CHARTEXT){
                    case 'F':
                    case 'f':
                    case 'Z':
                    food_wehave[numfood]=mvinch(user->position->y,user->position->x+1);
                    numfood++;
                    break;
                }
            }
            switch(mvinch(user->position->y,user->position->x+1) &A_CHARTEXT){
                case 'z':
                spell_wehave_number[0]+=1;
                break;
                case 'S':
                spell_wehave_number[1]+=1;
                break;
                case 'A':
                spell_wehave_number[2]+=1;
                break;
            }
            switch(mvinch(user->position->y,user->position->x+1) &A_CHARTEXT){
                case 'p':
                weapon_wehave_number[0]+=1;
                break;
                case 'x':
                weapon_wehave_number[1]+=10;
                break;
                case 'r':
                weapon_wehave_number[2]+=8;
                break;
                case 'v':
                weapon_wehave_number[3]+=20;
                break;
                case 't':
                weapon_wehave_number[4]=1;
                break;
            }
            mvprintw(user->position->y,user->position->x+1,".");
            map[0][user->position->y][user->position->x+1]=1;
            level->tiles=LEVEL();
            break;
        case 'e':
            eINPUT(user,level);
            break;
        case '0':
            move(37,0);
            clrtoeol();
            move(34,0);
            clrtoeol();
            move(35,0);
            clrtoeol();
            move(38,0);
            clrtoeol();
            break;
        case 'f':
                int type=rand()%2;
                if(type==1){
                    type=3;
                }
                while(1){
                    if(mvinch(34,0)=='f'){
                        CONSUMEFOOD(user,type,level);
                        for(int j=0;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,2)=='f'){
                        CONSUMEFOOD(user,type,level);
                        for(int j=1;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,4)=='f'){
                        CONSUMEFOOD(user,type,level);
                        for(int j=2;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,6)=='f'){
                        CONSUMEFOOD(user,type,level);
                        for(int j=3;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,8)=='f'){
                        CONSUMEFOOD(user,type,level);
                        for(int j=4;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    break;
                }
                break;
        case 'F':
                while(1){
                    if(mvinch(34,0)=='F'){
                        CONSUMEFOOD(user,1,level);
                        for(int j=0;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,2)=='F'){
                        CONSUMEFOOD(user,1,level);
                        for(int j=1;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,4)=='F'){
                        CONSUMEFOOD(user,1,level);
                        for(int j=2;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,6)=='F'){
                        CONSUMEFOOD(user,1,level);
                        for(int j=3;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,8)=='F'){
                        CONSUMEFOOD(user,1,level);
                        for(int j=4;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    break;
                }
                break;
        case 'Z':
                CONSUMEFOOD(user,2,level);
                while(1){
                    if(mvinch(34,0)=='Z'){
                        CONSUMEFOOD(user,2,level);
                        for(int j=0;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,2)=='Z'){
                        CONSUMEFOOD(user,2,level);
                        for(int j=1;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,4)=='Z'){
                        CONSUMEFOOD(user,2,level);
                        for(int j=2;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,6)=='Z'){
                        CONSUMEFOOD(user,2,level);
                        for(int j=3;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    else if(mvinch(34,8)=='Z'){
                        CONSUMEFOOD(user,2,level);
                        for(int j=4;j<numfood;j++){
                            food_wehave[j]=food_wehave[j+1];
                        }
                        numfood--;
                        EINPUT(user,level);
                        break;
                    }
                    break;
                }
                break;
        case 'i':
            iINPUT(user,level);
            break;
        case 'c':
            fast=1;
        break; 
        case 'p':
            if(weapon_wehave==0){
                if(weapon_wehave_number[0]!=0){
                    init_pair(37,COLOR_BLUE,COLOR_BLACK);
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ The MACE has been picked up.");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD); 
                    p=1;
                    x=0;
                    r=0;
                    v=0;
                    t=0; 
                    weapon_wehave=1;
                    init_pair(20,COLOR_WHITE,COLOR_BLUE);
                    attron(COLOR_PAIR(20));
                    attron(A_BOLD);
                    mvprintw(30,73,"WEAPON MACE p");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(20));
                }
                else{
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ This weapon is out of stock..");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD); 
                }
            }
            else{
                init_pair(37,COLOR_BLUE,COLOR_BLACK);
                attron(COLOR_PAIR(37));
                attron(A_BOLD);
                mvprintw(31,0,"   ^_^ First, place your previous weapon in your backpack.");
                attroff(COLOR_PAIR(37));
                attroff(A_BOLD);
            }
            refresh();
            time_t start_time=time(NULL);
                while(1){
                if(time(NULL)-start_time>=2){
                    break;
                }
            }
            refresh();
            move(31,0);
            clrtoeol();
            move(38,0);
            clrtoeol();
            refresh();
            break;
        case 'x':
            if(weapon_wehave==0){
                if(weapon_wehave_number[1]!=0){
                    init_pair(37,COLOR_BLUE,COLOR_BLACK);
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ The DAGGER has been picked up.");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD); 
                    p=0;
                    x=1;
                    r=0;
                    v=0;
                    t=0;  
                    weapon_wehave=2;
                    init_pair(20,COLOR_WHITE,COLOR_BLUE);
                    attron(COLOR_PAIR(20));
                    attron(A_BOLD);
                    mvprintw(30,73,"WEAPON DAGGER x");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(20));
                }
                else{
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ This weapon is out of stock..");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD); 
                }
            }
            else{
                init_pair(37,COLOR_BLUE,COLOR_BLACK);
                attron(COLOR_PAIR(37));
                attron(A_BOLD);
                mvprintw(31,0,"   ^_^ First, place your previous weapon in your backpack.");
                attroff(COLOR_PAIR(37));
                attroff(A_BOLD);
            }
            refresh();
            time_t start_time_x=time(NULL);
                while(1){
                if(time(NULL)-start_time_x>=2){
                    break;
                }
            }
            refresh();
            move(31,0);
            clrtoeol();
            move(38,0);
            clrtoeol();
            refresh();
            break;
        case 'r':
            if(weapon_wehave==0){
                if(weapon_wehave_number[2]!=0){
                    init_pair(37,COLOR_BLUE,COLOR_BLACK);
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ The MAGIC WAND has been picked up.");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD);  
                    weapon_wehave=3;
                    p=0;
                    x=0;
                    r=1;
                    v=0;
                    t=0;
                    init_pair(20,COLOR_WHITE,COLOR_BLUE);
                    attron(COLOR_PAIR(20));
                    attron(A_BOLD);
                    mvprintw(30,73,"WEAPON MAGIC WAND r");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(20));  
                }
                else{
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ This weapon is out of stock..");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD); 
                }
            }
            else{
                init_pair(37,COLOR_BLUE,COLOR_BLACK);
                attron(COLOR_PAIR(37));
                attron(A_BOLD);
                mvprintw(31,0,"   ^_^ First, place your previous weapon in your backpack.");
                attroff(COLOR_PAIR(37));
                attroff(A_BOLD);
            }
            break;
            refresh();
            time_t start_time_r=time(NULL);
                while(1){
                if(time(NULL)-start_time_r>=2){
                    break;
                }
            }
            refresh();
            move(31,0);
            clrtoeol();
            move(38,0);
            clrtoeol();
            refresh();
        case 'v':
            if(weapon_wehave==0){
                if(weapon_wehave_number[3]!=0){
                    init_pair(37,COLOR_BLUE,COLOR_BLACK);
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ The NORMAL ARROW has been picked up.");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD);  
                    weapon_wehave=4;
                    p=0;
                    x=0;
                    r=0;
                    v=1;
                    t=0;
                    init_pair(20,COLOR_WHITE,COLOR_BLUE);
                    attron(COLOR_PAIR(20));
                    attron(A_BOLD);
                    mvprintw(30,73,"WEAPON NORMALL ARROW v");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(20));  
                }
                else{
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ This weapon is out of stock..");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD); 
                }
            }
            else{
                init_pair(37,COLOR_BLUE,COLOR_BLACK);
                attron(COLOR_PAIR(37));
                attron(A_BOLD);
                mvprintw(31,0,"   ^_^ First, place your previous weapon in your backpack.");
                attroff(COLOR_PAIR(37));
                attroff(A_BOLD);
            }
            refresh();
            time_t start_time_v=time(NULL);
                while(1){
                if(time(NULL)-start_time_v>=2){
                    break;
                }
            }
            refresh();
            move(31,0);
            clrtoeol();
            move(38,0);
            clrtoeol();
            refresh();
            break;
        case 't':
            if(weapon_wehave==0){
                if(weapon_wehave_number[4]!=0){
                    init_pair(37,COLOR_BLUE,COLOR_BLACK);
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ The SWORD has been picked up.");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD);  
                    weapon_wehave=5;
                    p=0;
                    x=0;
                    r=0;
                    v=0;
                    t=1; 
                    init_pair(20,COLOR_WHITE,COLOR_BLUE);
                    attron(COLOR_PAIR(20));
                    attron(A_BOLD);
                    mvprintw(30,73,"WEAPON SWORD t");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(20));    
                }
                else{
                    attron(COLOR_PAIR(37));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ This weapon is out of stock..");
                    attroff(COLOR_PAIR(37));
                    attroff(A_BOLD); 
                }
            }
            else{
                init_pair(37,COLOR_BLUE,COLOR_BLACK);
                attron(COLOR_PAIR(37));
                attron(A_BOLD);
                mvprintw(31,0,"   ^_^ First, place your previous weapon in your backpack.");
                attroff(COLOR_PAIR(37));
                attroff(A_BOLD);
            }
            refresh();
            time_t start_time_t=time(NULL);
                while(1){
                if(time(NULL)-start_time_t>=2){
                    break;
                }
            }
            refresh();
            move(31,0);
            clrtoeol();
            move(38,0);
            clrtoeol();
            refresh();
            break;
        case '<':
            clear(); 
            int x=0;
            int y=0;
            int z=0;
            if(level->level==2){
                level->level--;
                GAMELINE(level);   
                FILE * file=fopen("level1.txt","r");
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            fscanf(file,"%d",MAP[i][j]+k);
                        }
                    }
                }
                fclose(file);

                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            if(MAP[i][j][k]==1){
                                mvprintw(j,k,".");
                            }
                            if(MAP[i][j][k]==2){
                                if(i==0){
                                    attron(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attron(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attron(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attron(COLOR_PAIR(33));
                                }
                                mvprintw(j,k,"-");
                                if(i==0){
                                    attroff(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attroff(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attroff(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attroff(COLOR_PAIR(33));
                                }
                            }
                            if(MAP[i][j][k]==3){
                                if(i==0){
                                    attron(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attron(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attron(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attron(COLOR_PAIR(33));
                                }
                                mvprintw(j,k,"|");
                                if(i==0){
                                    attroff(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attroff(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attroff(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attroff(COLOR_PAIR(33));
                                }
                            }
                            if(MAP[i][j][k]==4){
                                attron(COLOR_PAIR(13));
                                mvprintw(j,k,"@");
                                attroff(COLOR_PAIR(13));
                            }
                            if(MAP[i][j][k]==5){
                                if(i==0){
                                    attron(COLOR_PAIR(3));
                                }
                                else if(i==1){
                                    attron(COLOR_PAIR(12));
                                }
                                mvprintw(j,k,"o");
                                if(i==0){
                                    attroff(COLOR_PAIR(3));
                                }
                                else if(i==1){
                                    attroff(COLOR_PAIR(12));
                                }
                            
                            }
                            if(MAP[i][j][k]==6){
                                mvprintw(j,k,"&");
                            }
                            if(MAP[i][j][k]==7){
                                mvprintw(j,k,"=");
                            }
                            if(MAP[i][j][k]==8){
                                mvprintw(j,k,"+");
                            }
                            if(MAP[i][j][k]==9){
                                mvprintw(j,k,"<");
                            }
                            if(MAP[i][j][k]==13){
                                mvprintw(j,k,"?");
                            }
                            if(MAP[i][j][k]==11){
                                attron(COLOR_PAIR(11));
                                mvprintw(j,k,"g");
                                attroff(COLOR_PAIR(11));
                            }
                            if(MAP[i][j][k]==12){
                                attron(COLOR_PAIR(11));
                                mvprintw(j,k,"s");
                                attroff(COLOR_PAIR(11));
                            }
                            if(MAP[i][j][k]==10){
                                attron(COLOR_PAIR(36));
                                attron(A_BOLD);
                                mvprintw(j,k,"O");
                                attroff(A_BOLD);
                                attroff(COLOR_PAIR(36));
                            }
                            if(MAP[i][j][k]==20){
                                mvprintw(j,k,"f");
                            }
                            if(MAP[i][j][k]==21){
                                mvprintw(j,k,"F");
                            }
                            if(MAP[i][j][k]==10){
                                attron(COLOR_PAIR(36));
                                attron(A_BOLD);
                                mvprintw(j,k,"O");
                                attroff(A_BOLD);
                                attroff(COLOR_PAIR(36));
                            }
                            if(MAP[i][j][k]==22){
                                mvprintw(j,k,"Z");
                            }
                            if(MAP[i][j][k]==30){
                                init_pair(15,COLOR_BLACK,COLOR_YELLOW);
                                attron(COLOR_PAIR(15));
                                mvprintw(j,k,"G");
                                attroff(COLOR_PAIR(15));
                            }
                            if(MAP[i][j][k]==31){
                                init_pair(16,COLOR_BLACK,COLOR_CYAN);
                                attron(COLOR_PAIR(16));
                                mvprintw(j,k,"C");
                                attroff(COLOR_PAIR(16));
                            }
                            if(MAP[i][j][k]==40){
                                init_pair(40,COLOR_WHITE,COLOR_MAGENTA);
                                attron(COLOR_PAIR(40));
                                mvprintw(j,k,"z");
                                attroff(COLOR_PAIR(40));
                            }
                            if(MAP[i][j][k]==41){
                                init_pair(17,COLOR_BLUE,COLOR_MAGENTA);
                                attron(COLOR_PAIR(17));
                                mvprintw(j,k,"S");
                                attroff(COLOR_PAIR(17));
                            }
                            if(MAP[i][j][k]==42){
                                init_pair(18,COLOR_BLACK,COLOR_MAGENTA);
                                attron(COLOR_PAIR(18));
                                mvprintw(j,k,"A");
                                attroff(COLOR_PAIR(18));
                            }
                            if(MAP[i][j][k]==43){
                                init_pair(43,COLOR_RED,COLOR_BLACK);
                                attron(COLOR_PAIR(43));
                                mvprintw(j,k,"^");
                                attroff(COLOR_PAIR(43));
                            }
                            if(MAP[i][j][k]==50){
                                init_pair(20,COLOR_WHITE,COLOR_BLUE);
                                attron(COLOR_PAIR(20));
                                mvprintw(j,k,"p");
                                attroff(COLOR_PAIR(20));
                            }
                            if(MAP[i][j][k]==52){
                                init_pair(22,COLOR_GREEN,COLOR_BLUE);
                                attron(COLOR_PAIR(22));
                                mvprintw(j,k,"r");
                                attroff(COLOR_PAIR(22));
                            }
                            if(MAP[i][j][k]==51){
                                init_pair(21,COLOR_CYAN,COLOR_BLUE);
                                attron(COLOR_PAIR(21));
                                mvprintw(j,k,"x");
                                attroff(COLOR_PAIR(21));
                            }
                            if(MAP[i][j][k]==53){
                                init_pair(23,COLOR_RED,COLOR_BLUE);
                                attron(COLOR_PAIR(23));
                                mvprintw(j,k,"v");
                                attroff(COLOR_PAIR(23));
                            }
                            if(MAP[i][j][k]==54){
                                init_pair(24,COLOR_BLACK,COLOR_BLUE);
                                attron(COLOR_PAIR(24));
                                mvprintw(j,k,"t");
                                attroff(COLOR_PAIR(24));
                            }
                            if(MAP[i][j][k]==15){
                                mvprintw(j,k,"#");
                            }
                            if(MAP[i][j][k]==16){
                                attron(COLOR_PAIR(30));
                                mvprintw(j,k,"|");
                                attroff(COLOR_PAIR(30));
                                
                            }
                        }
                    }
                }
                int x=0;
                int y=0;
                int z=0;
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            if(map[i][j][k]==1){
                                x=i;
                                y=j;
                                z=k;
                                break;
                            }
                        }
                    }
                }
            }
            if(level->level==3){
                level->level--;
                GAMELINE(level);   
                FILE * file=fopen("level2.txt","r");
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            fscanf(file,"%d",MAP[i][j]+k);
                        }
                    }
                }
                fclose(file);

                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            if(MAP[i][j][k]==1){
                                mvprintw(j,k,".");
                            }
                            if(MAP[i][j][k]==2){
                                if(i==0){
                                    attron(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attron(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attron(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attron(COLOR_PAIR(33));
                                }
                                mvprintw(j,k,"-");
                                if(i==0){
                                    attroff(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attroff(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attroff(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attroff(COLOR_PAIR(33));
                                }
                            }
                            if(MAP[i][j][k]==3){
                                if(i==0){
                                    attron(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attron(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attron(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attron(COLOR_PAIR(33));
                                }
                                mvprintw(j,k,"|");
                                if(i==0){
                                    attroff(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attroff(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attroff(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attroff(COLOR_PAIR(33));
                                }
                            }
                            if(MAP[i][j][k]==4){
                                attron(COLOR_PAIR(13));
                                mvprintw(j,k,"@");
                                attroff(COLOR_PAIR(13));
                            }
                            if(MAP[i][j][k]==5){
                                if(i==0){
                                    attron(COLOR_PAIR(3));
                                }
                                else if(i==1){
                                    attron(COLOR_PAIR(12));
                                }
                                mvprintw(j,k,"o");
                                if(i==0){
                                    attroff(COLOR_PAIR(3));
                                }
                                else if(i==1){
                                    attroff(COLOR_PAIR(12));
                                }
                            
                            }
                            if(MAP[i][j][k]==6){
                                mvprintw(j,k,"&");
                            }
                            if(MAP[i][j][k]==7){
                                mvprintw(j,k,"=");
                            }
                            if(MAP[i][j][k]==8){
                                mvprintw(j,k,"+");
                            }
                            if(MAP[i][j][k]==9){
                                mvprintw(j,k,"<");
                            }
                            if(MAP[i][j][k]==13){
                                mvprintw(j,k,"?");
                            }
                            if(MAP[i][j][k]==11){
                                attron(COLOR_PAIR(11));
                                mvprintw(j,k,"g");
                                attroff(COLOR_PAIR(11));
                            }
                            if(MAP[i][j][k]==12){
                                attron(COLOR_PAIR(11));
                                mvprintw(j,k,"s");
                                attroff(COLOR_PAIR(11));
                            }
                            if(MAP[i][j][k]==10){
                                attron(COLOR_PAIR(36));
                                attron(A_BOLD);
                                mvprintw(j,k,"O");
                                attroff(A_BOLD);
                                attroff(COLOR_PAIR(36));
                            }
                            if(MAP[i][j][k]==20){
                                mvprintw(j,k,"f");
                            }
                            if(MAP[i][j][k]==21){
                                mvprintw(j,k,"F");
                            }
                            if(MAP[i][j][k]==10){
                                attron(COLOR_PAIR(36));
                                attron(A_BOLD);
                                mvprintw(j,k,"O");
                                attroff(A_BOLD);
                                attroff(COLOR_PAIR(36));
                            }
                            if(MAP[i][j][k]==22){
                                mvprintw(j,k,"Z");
                            }
                            if(MAP[i][j][k]==30){
                                init_pair(15,COLOR_BLACK,COLOR_YELLOW);
                                attron(COLOR_PAIR(15));
                                mvprintw(j,k,"G");
                                attroff(COLOR_PAIR(15));
                            }
                            if(MAP[i][j][k]==31){
                                init_pair(16,COLOR_BLACK,COLOR_CYAN);
                                attron(COLOR_PAIR(16));
                                mvprintw(j,k,"C");
                                attroff(COLOR_PAIR(16));
                            }
                            if(MAP[i][j][k]==40){
                                init_pair(40,COLOR_WHITE,COLOR_MAGENTA);
                                attron(COLOR_PAIR(40));
                                mvprintw(j,k,"z");
                                attroff(COLOR_PAIR(40));
                            }
                            if(MAP[i][j][k]==41){
                                init_pair(17,COLOR_BLUE,COLOR_MAGENTA);
                                attron(COLOR_PAIR(17));
                                mvprintw(j,k,"S");
                                attroff(COLOR_PAIR(17));
                            }
                            if(MAP[i][j][k]==42){
                                init_pair(18,COLOR_BLACK,COLOR_MAGENTA);
                                attron(COLOR_PAIR(18));
                                mvprintw(j,k,"A");
                                attroff(COLOR_PAIR(18));
                            }
                            if(MAP[i][j][k]==43){
                                init_pair(43,COLOR_RED,COLOR_BLACK);
                                attron(COLOR_PAIR(43));
                                mvprintw(j,k,"^");
                                attroff(COLOR_PAIR(43));
                            }
                            if(MAP[i][j][k]==50){
                                init_pair(20,COLOR_WHITE,COLOR_BLUE);
                                attron(COLOR_PAIR(20));
                                mvprintw(j,k,"p");
                                attroff(COLOR_PAIR(20));
                            }
                            if(MAP[i][j][k]==52){
                                init_pair(22,COLOR_GREEN,COLOR_BLUE);
                                attron(COLOR_PAIR(22));
                                mvprintw(j,k,"r");
                                attroff(COLOR_PAIR(22));
                            }
                            if(MAP[i][j][k]==51){
                                init_pair(21,COLOR_CYAN,COLOR_BLUE);
                                attron(COLOR_PAIR(21));
                                mvprintw(j,k,"x");
                                attroff(COLOR_PAIR(21));
                            }
                            if(MAP[i][j][k]==53){
                                init_pair(23,COLOR_RED,COLOR_BLUE);
                                attron(COLOR_PAIR(23));
                                mvprintw(j,k,"v");
                                attroff(COLOR_PAIR(23));
                            }
                            if(MAP[i][j][k]==54){
                                init_pair(24,COLOR_BLACK,COLOR_BLUE);
                                attron(COLOR_PAIR(24));
                                mvprintw(j,k,"t");
                                attroff(COLOR_PAIR(24));
                            }
                            if(MAP[i][j][k]==15){
                                mvprintw(j,k,"#");
                            }
                            if(MAP[i][j][k]==16){
                                attron(COLOR_PAIR(30));
                                mvprintw(j,k,"|");
                                attroff(COLOR_PAIR(30));
                                
                            }
                        }
                    }
                }
                int x=0;
                int y=0;
                int z=0;
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            if(map[i][j][k]==1){
                                x=i;
                                y=j;
                                z=k;
                                break;
                            }
                        }
                    }
                }
            }
            if(level->level==4){
                level->level--;
                GAMELINE(level);   
                FILE * file=fopen("level3.txt","r");
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            fscanf(file,"%d",MAP[i][j]+k);
                        }
                    }
                }
                fclose(file);

                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            if(MAP[i][j][k]==1){
                                mvprintw(j,k,".");
                            }
                            if(MAP[i][j][k]==2){
                                if(i==0){
                                    attron(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attron(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attron(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attron(COLOR_PAIR(33));
                                }
                                mvprintw(j,k,"-");
                                if(i==0){
                                    attroff(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attroff(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attroff(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attroff(COLOR_PAIR(33));
                                }
                            }
                            if(MAP[i][j][k]==3){
                                if(i==0){
                                    attron(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attron(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attron(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attron(COLOR_PAIR(33));
                                }
                                mvprintw(j,k,"|");
                                if(i==0){
                                    attroff(COLOR_PAIR(2));
                                }
                                else if(i==1){
                                    attroff(COLOR_PAIR(10));
                                }
                                else if(i==2){
                                    attroff(COLOR_PAIR(30));
                                }
                                else if(i==3){
                                    attroff(COLOR_PAIR(33));
                                }
                            }
                            if(MAP[i][j][k]==4){
                                attron(COLOR_PAIR(13));
                                mvprintw(j,k,"@");
                                attroff(COLOR_PAIR(13));
                            }
                            if(MAP[i][j][k]==5){
                                if(i==0){
                                    attron(COLOR_PAIR(3));
                                }
                                else if(i==1){
                                    attron(COLOR_PAIR(12));
                                }
                                mvprintw(j,k,"o");
                                if(i==0){
                                    attroff(COLOR_PAIR(3));
                                }
                                else if(i==1){
                                    attroff(COLOR_PAIR(12));
                                }
                            
                            }
                            if(MAP[i][j][k]==6){
                                mvprintw(j,k,"&");
                            }
                            if(MAP[i][j][k]==7){
                                mvprintw(j,k,"=");
                            }
                            if(MAP[i][j][k]==8){
                                mvprintw(j,k,"+");
                            }
                            if(MAP[i][j][k]==9){
                                mvprintw(j,k,"<");
                            }
                            if(MAP[i][j][k]==13){
                                mvprintw(j,k,"?");
                            }
                            if(MAP[i][j][k]==11){
                                attron(COLOR_PAIR(11));
                                mvprintw(j,k,"g");
                                attroff(COLOR_PAIR(11));
                            }
                            if(MAP[i][j][k]==12){
                                attron(COLOR_PAIR(11));
                                mvprintw(j,k,"s");
                                attroff(COLOR_PAIR(11));
                            }
                            if(MAP[i][j][k]==10){
                                attron(COLOR_PAIR(36));
                                attron(A_BOLD);
                                mvprintw(j,k,"O");
                                attroff(A_BOLD);
                                attroff(COLOR_PAIR(36));
                            }
                            if(MAP[i][j][k]==20){
                                mvprintw(j,k,"f");
                            }
                            if(MAP[i][j][k]==21){
                                mvprintw(j,k,"F");
                            }
                            if(MAP[i][j][k]==10){
                                attron(COLOR_PAIR(36));
                                attron(A_BOLD);
                                mvprintw(j,k,"O");
                                attroff(A_BOLD);
                                attroff(COLOR_PAIR(36));
                            }
                            if(MAP[i][j][k]==22){
                                mvprintw(j,k,"Z");
                            }
                            if(MAP[i][j][k]==30){
                                init_pair(15,COLOR_BLACK,COLOR_YELLOW);
                                attron(COLOR_PAIR(15));
                                mvprintw(j,k,"G");
                                attroff(COLOR_PAIR(15));
                            }
                            if(MAP[i][j][k]==31){
                                init_pair(16,COLOR_BLACK,COLOR_CYAN);
                                attron(COLOR_PAIR(16));
                                mvprintw(j,k,"C");
                                attroff(COLOR_PAIR(16));
                            }
                            if(MAP[i][j][k]==40){
                                init_pair(40,COLOR_WHITE,COLOR_MAGENTA);
                                attron(COLOR_PAIR(40));
                                mvprintw(j,k,"z");
                                attroff(COLOR_PAIR(40));
                            }
                            if(MAP[i][j][k]==41){
                                init_pair(17,COLOR_BLUE,COLOR_MAGENTA);
                                attron(COLOR_PAIR(17));
                                mvprintw(j,k,"S");
                                attroff(COLOR_PAIR(17));
                            }
                            if(MAP[i][j][k]==42){
                                init_pair(18,COLOR_BLACK,COLOR_MAGENTA);
                                attron(COLOR_PAIR(18));
                                mvprintw(j,k,"A");
                                attroff(COLOR_PAIR(18));
                            }
                            if(MAP[i][j][k]==43){
                                init_pair(43,COLOR_RED,COLOR_BLACK);
                                attron(COLOR_PAIR(43));
                                mvprintw(j,k,"^");
                                attroff(COLOR_PAIR(43));
                            }
                            if(MAP[i][j][k]==50){
                                init_pair(20,COLOR_WHITE,COLOR_BLUE);
                                attron(COLOR_PAIR(20));
                                mvprintw(j,k,"p");
                                attroff(COLOR_PAIR(20));
                            }
                            if(MAP[i][j][k]==52){
                                init_pair(22,COLOR_GREEN,COLOR_BLUE);
                                attron(COLOR_PAIR(22));
                                mvprintw(j,k,"r");
                                attroff(COLOR_PAIR(22));
                            }
                            if(MAP[i][j][k]==51){
                                init_pair(21,COLOR_CYAN,COLOR_BLUE);
                                attron(COLOR_PAIR(21));
                                mvprintw(j,k,"x");
                                attroff(COLOR_PAIR(21));
                            }
                            if(MAP[i][j][k]==53){
                                init_pair(23,COLOR_RED,COLOR_BLUE);
                                attron(COLOR_PAIR(23));
                                mvprintw(j,k,"v");
                                attroff(COLOR_PAIR(23));
                            }
                            if(MAP[i][j][k]==54){
                                init_pair(24,COLOR_BLACK,COLOR_BLUE);
                                attron(COLOR_PAIR(24));
                                mvprintw(j,k,"t");
                                attroff(COLOR_PAIR(24));
                            }
                            if(MAP[i][j][k]==15){
                                mvprintw(j,k,"#");
                            }
                            if(MAP[i][j][k]==16){
                                attron(COLOR_PAIR(30));
                                mvprintw(j,k,"|");
                                attroff(COLOR_PAIR(30));
                                
                            }
                        }
                    }
                }
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            if(map[i][j][k]==1){
                                x=i;
                                y=j;
                                z=k;
                                break;
                            }
                        }
                    }
                }
            }
            
            move(3,3);
            //mvprintw(3,3,"$");
            move(y,z);
            timerepet++;
            level->tiles=LEVEL();
            break;
        case 'z':
            CONSUMESPELL(user,0,level);
            spell_wehave_number[0]-=1;
            eINPUT(user,level);
            break;
        case 'S':
            CONSUMESPELL(user,1,level);
            spell_wehave_number[1]-=1;
            eINPUT(user,level);
            break;
        case 'A':
            CONSUMESPELL(user,2,level);
            spell_wehave_number[2]-=1;
            eINPUT(user,level);
            break;
        case 'M':
            if(show_or_not==1){
                show_or_not=0;
            }
            else{
                show_or_not=1;
            }
       // if(show_or_not==1){
            for(int i=0;i<6;i++){
                findroomprim[i]=Findroom[i];
                dra[i]=drawconnect_yes_or_no[i];
                drawroomprim[i]=Drawroom[i];
                Findroom[i]=1;
                drawconnect_yes_or_no[i]=1;
            }
            DRAWROOM(level->rooms);
            for(int i=0;i<50;i++){
                for(int j=0;j<200;j++){
                    if(trapplace[i][j]==1){
                        init_pair(43,COLOR_RED,COLOR_BLACK);
                        attron(COLOR_PAIR(43));
                        mvprintw(i,j,"^");
                        attroff(COLOR_PAIR(43));
                    }
                }
            }
            WHEREISPLAYER(level->rooms, level->user);
       // }
        // if(show_or_not==0){
        //     for(int i=0;i<6;i++){
        //         Drawroom[i]=drawroomprim[i];
        //         Findroom[i]=findroomprim[i];
        //         drawconnect_yes_or_no[i]=dra[i];
        //     }
        //     DRAWROOM(level->rooms);
        //     WHEREISPLAYER(level->rooms, level->user);
        // }
            break;
        case KEY_UP:
                wscrl(stdscr, -1);
                break;
        case KEY_DOWN:
                wscrl(stdscr, 1);
                break;
        case ' ':
            if(p==1){
                pl=1;
                vl=0;
                xl=0;
                tl=0;
                rl=0;
            }
            else if(t==1){
                pl=0;
                vl=0;
                xl=0;
                tl=1;
                rl=0;
            }
            else if(x==1){
                pl=0;
                vl=0;
                xl=1;
                tl=0;
                rl=0;
            }
            else if(v==1){
                pl=0;
                vl=1;
                xl=0;
                tl=0;
                rl=0;
            }
            else if(r==1){
                pl=0;
                vl=0;
                xl=0;
                tl=0;
                rl=1;
            }
            switch(mvinch(user->position->y,user->position->x-1)&A_CHARTEXT){
                case 'D':
                    mvprintw(user->position->y,user->position->x-1,".");
                    map[0][user->position->y][user->position->x-1]=1;
                    level->tiles=LEVEL();
                    init_pair(65,COLOR_RED,COLOR_BLACK);
                    attron(COLOR_PAIR(65));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ You have killed a DEMON!");
                    attroff(COLOR_PAIR(65));
                    attroff(A_BOLD);
                    user->score+=1;
                    weapon_wehave=0;
                    if(pl==1){
                        p=0;
                        pl=0;
                        weapon_wehave_number[0]-=1;
                    }
                    else if(tl==1){
                        t=0;
                        tl=0;
                        weapon_wehave_number[4]-=1;
                    }
                    move(30,0);
                    clrtoeol();
                    GAMELINE(level);
                    break;
                case 'P':
                    if(tl==1){
                        mvprintw(user->position->y,user->position->x-1,".");
                        map[0][user->position->y][user->position->x-1]=1;
                        level->tiles=LEVEL();
                        init_pair(65,COLOR_RED,COLOR_BLACK);
                        attron(COLOR_PAIR(65));
                        attron(A_BOLD);
                        mvprintw(31,0,"   ^_^ You have killed a DEMON!");
                        attroff(COLOR_PAIR(65));
                        attroff(A_BOLD);
                        user->score+=3;
                        weapon_wehave=0;
                        t=0;
                        tl=0;
                        weapon_wehave_number[4]-=1;
                        move(30,0);
                        clrtoeol();
                        GAMELINE(level);
                    }
                
                
            }
            switch(mvinch(user->position->y,user->position->x+1)&A_CHARTEXT){
                case 'D': 
                    mvprintw(user->position->y,user->position->x+1,".");
                    map[0][user->position->y][user->position->x+1]=1;
                    level->tiles=LEVEL();
                    init_pair(65,COLOR_RED,COLOR_BLACK);
                    attron(COLOR_PAIR(65));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ You have killed a DEMON!");
                    attroff(COLOR_PAIR(65));
                    attroff(A_BOLD);
                    user->score+=1;
                    weapon_wehave=0;
                    if(pl==1){
                        p=0;
                        pl=0;
                        weapon_wehave_number[0]-=1;
                    }
                    if(tl==1){
                        t=0;
                        tl=0;
                        weapon_wehave_number[4]-=1;
                    }
                    move(30,0);
                    clrtoeol();
                    GAMELINE(level);
                    break;
                
            }
            switch(mvinch(user->position->y+1,user->position->x)&A_CHARTEXT){
                case 'D':
                    mvprintw(user->position->y+1,user->position->x,".");
                    map[0][user->position->y+1][user->position->x]=1;
                    level->tiles=LEVEL();
                    init_pair(65,COLOR_RED,COLOR_BLACK);
                    attron(COLOR_PAIR(65));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ You have killed a DEMON!");
                    attroff(COLOR_PAIR(65));
                    attroff(A_BOLD);
                    user->score+=1;
                   if(pl==1){
                        p=0;
                        pl=0;
                        weapon_wehave_number[0]-=1;
                    }
                    if(tl==1){
                        t=0;
                        tl=0;
                        weapon_wehave_number[4]-=1;
                    }
                    weapon_wehave=0;
                    move(30,0);
                    clrtoeol();
                    GAMELINE(level);
                    break;
        
            }
            switch(mvinch(user->position->y+1,user->position->x+1)&A_CHARTEXT){
                case 'D':
                    mvprintw(user->position->y+1,user->position->x+1,".");
                    map[0][user->position->y+1][user->position->x+1]=1;
                    level->tiles=LEVEL();
                    init_pair(65,COLOR_RED,COLOR_BLACK);
                    attron(COLOR_PAIR(65));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ You have killed a DEMON!");
                    attroff(COLOR_PAIR(65));
                    attroff(A_BOLD);
                    user->score+=1;
                    if(pl==1){
                        p=0;
                        pl=0;
                        weapon_wehave_number[0]-=1;
                    }
                    if(tl==1){
                        t=0;
                        tl=0;
                        weapon_wehave_number[4]-=1;
                    }
                    weapon_wehave=0;
                    move(30,0);
                    clrtoeol();
                    GAMELINE(level);
                    break;
                
            }
            switch(mvinch(user->position->y-1,user->position->x-1)&A_CHARTEXT){
                case 'D':
                    mvprintw(user->position->y-1,user->position->x-1,".");
                    map[0][user->position->y-1][user->position->x-1]=1;
                    level->tiles=LEVEL();
                    init_pair(65,COLOR_RED,COLOR_BLACK);
                    attron(COLOR_PAIR(65));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ You have killed a DEMON!");
                    attroff(COLOR_PAIR(65));
                    attroff(A_BOLD);
                    user->score+=1;
                    if(pl==1){
                        p=0;
                        pl=0;
                        weapon_wehave_number[0]-=1;
                    }
                    if(tl==1){
                        t=0;
                        tl=0;
                        weapon_wehave_number[4]-=1;
                    }
                    weapon_wehave=0;
                    move(30,0);
                    clrtoeol();
                    GAMELINE(level);
                    break;
                
            }
            switch(mvinch(user->position->y+1,user->position->x-1)&A_CHARTEXT){
                case 'D':
                
                    mvprintw(user->position->y+1,user->position->x-1,".");
                    map[0][user->position->y+1][user->position->x-1]=1;
                    level->tiles=LEVEL();
                    init_pair(65,COLOR_RED,COLOR_BLACK);
                    attron(COLOR_PAIR(65));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ You have killed a DEMON!");
                    attroff(COLOR_PAIR(65));
                    attroff(A_BOLD);
                    user->score+=1;
                    if(pl==1){
                        p=0;
                        pl=0;
                        weapon_wehave_number[0]-=1;
                    }
                    if(tl==1){
                        t=0;
                        tl=0;
                        weapon_wehave_number[4]-=1;
                    }
                    weapon_wehave=0;
                    move(30,0);
                    clrtoeol();
                    GAMELINE(level);
                    break;
                
            }
            switch(mvinch(user->position->y-1,user->position->x+1)&A_CHARTEXT){
                case 'D':
                    mvprintw(user->position->y-1,user->position->x+1,".");
                    map[0][user->position->y-1][user->position->x+1]=1;
                    level->tiles=LEVEL();
                    init_pair(65,COLOR_RED,COLOR_BLACK);
                    attron(COLOR_PAIR(65));
                    attron(A_BOLD);
                    mvprintw(31,0,"   ^_^ You have killed a DEMON!");
                    attroff(COLOR_PAIR(65));
                    attroff(A_BOLD);
                    user->score+=1;
                    if(pl==1){
                        p=0;
                        pl=0;
                        weapon_wehave_number[0]-=1;
                    }
                    if(tl==1){
                        t=0;
                        tl=0;
                        weapon_wehave_number[4]-=1;
                    }
                    weapon_wehave=0;
                    move(30,0);
                    clrtoeol();
                    GAMELINE(level);
                    break;
                
            }
            
            break;
        case 'g':
            if(g==1){
                g=0;
            }
            else{
                g=1;
            }
            break;
        case 'G':
            CONSUMEGOLD(user,0,level);
            mvprintw(user->position->y,user->position->x+1,".");
            map[0][user->position->y][user->position->x+1]=1;
            level->tiles=LEVEL();
            int room_number=get_room_number(user,level);
            if(room_number==0 || room_number==3 || room_number==5){
                map[0][user->position->y][user->position->x+1]=1;
            }
            else if(room_number==1 || room_number==4){
                map[2][user->position->y][user->position->x+1]=1;
            }
            else if(timerepet==4 && room_number==3){
                map[3][user->position->y][user->position->x+1]=1;
            }
            init_pair(32,COLOR_YELLOW,COLOR_BLACK);
            attron(COLOR_PAIR(32));
            attron(A_BOLD);
            mvprintw(31,0,"   ^_^ Great job on winning gold!Keep going, the adventure continues!");
            attroff(COLOR_PAIR(32));
            attroff(A_BOLD);
            break;
        case 'C':
            CONSUMEGOLD(user,1,level);
            mvprintw(user->position->y,user->position->x-1,".");
            map[0][user->position->y][user->position->x+1]=1;
            level->tiles=LEVEL();
            int room_numberr=get_room_number(user,level);
            if(room_numberr==0 || room_numberr==3 || room_numberr==5){
                map[0][user->position->y][user->position->x+1]=1;
            }
            else if(room_numberr==1 || room_numberr==4){
                map[2][user->position->y][user->position->x+1]=1;
            }
            else if(timerepet==4 && room_numberr==3){
                map[3][user->position->y][user->position->x+1]=1;
            }
            init_pair(32,COLOR_YELLOW,COLOR_BLACK);
            attron(COLOR_PAIR(32));
            attron(A_BOLD);
            mvprintw(31,0,"   ^_^ Great job on winning GOLD!Keep going, the adventure continues!");
            attroff(COLOR_PAIR(32));
            attroff(A_BOLD);
            break;
        default:
            break;

    }
        
    return newP;
}

int CHECK(POSITION * newP,LEVELs * level,FOOD * food,int ch){

    Player * user;
    user=level->user;

    switch(mvinch(newP->y,newP->x)&A_CHARTEXT){
        case '.':
            if(trapplace[newP->y][newP->x]==1){
                init_pair(43,COLOR_RED,COLOR_BLACK);
                attron(COLOR_PAIR(43));
                mvprintw(newP->y,newP->x,"^");
                attroff(COLOR_PAIR(43));
            }
            else{
             PMOVE(newP,user,level);
            }
            break;
        case '+':
            if(newP->y==level->rooms[0]->DOOR[1]->y && newP->x==level->rooms[0]->DOOR[1]->x){
                drawconnect_yes_or_no[0]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[3]->DOOR[0]->y && newP->x==level->rooms[3]->DOOR[0]->x){
                drawconnect_yes_or_no[0]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[0]->DOOR[3]->y && newP->x==level->rooms[0]->DOOR[3]->x){
                drawconnect_yes_or_no[5]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[1]->DOOR[2]->y && newP->x==level->rooms[1]->DOOR[2]->x){
                drawconnect_yes_or_no[5]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[3]->DOOR[3]->y && newP->x==level->rooms[3]->DOOR[3]->x){
                drawconnect_yes_or_no[1]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[5]->DOOR[2]->y && newP->x==level->rooms[5]->DOOR[2]->x){
                    drawconnect_yes_or_no[2]=1;
                    DRAWROOM(level->rooms);
                    level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[2]->DOOR[2]->y && newP->x==level->rooms[2]->DOOR[2]->x){
                drawconnect_yes_or_no[4]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[5]->DOOR[0]->y && newP->x==level->rooms[5]->DOOR[0]->x){
                drawconnect_yes_or_no[3]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if(mvinch(newP->y,newP->x+1)=='#' || mvinch(newP->y+1,newP->x)=='#' || mvinch(newP->y,newP->x-1)=='#' || mvinch(newP->y-1,newP->x)=='#'){
                attron(COLOR_PAIR(2));
                attron(A_BOLD);
                mvprintw(31,0,"   ^_^ You have left the room.");
                attroff(COLOR_PAIR(2));
                attroff(A_BOLD);
                //PMOVE(newP,user,level);
                refresh();
                time_t start_time=time(NULL);
                while(1){
                if(time(NULL)-start_time>=2){
                    
                    break;
                }
                }
                PMOVE(newP,user,level);
                break;
            }
            else{
                attron(COLOR_PAIR(2));
                attron(A_BOLD);
                mvprintw(31,0,"   ^_^ You have entered the room.");
                attroff(COLOR_PAIR(2));
                attroff(A_BOLD);
                refresh();
                time_t start_time=time(NULL);
                while(1){
                if(time(NULL)-start_time>=2){
                    
                    break;
                }
                }
                PMOVE(newP,user,level);
                break;
            }
            break;
        case '?':
            if(newP->y==level->rooms[4]->DOOR[3]->y && newP->x==level->rooms[4]->DOOR[3]->x){
                    drawconnect_yes_or_no[2]=1;
                    DRAWROOM(level->rooms);
                    level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[1]->DOOR[3]->y && newP->x==level->rooms[1]->DOOR[3]->x){
                    drawconnect_yes_or_no[4]=1;
                    DRAWROOM(level->rooms);
                    level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[4]->DOOR[2]->y && newP->x==level->rooms[4]->DOOR[2]->x){
                drawconnect_yes_or_no[1]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if(newP->y==level->rooms[1]->DOOR[3]->y && newP->x==level->rooms[1]->DOOR[3]->x){
                drawconnect_yes_or_no[4]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if(mvinch(newP->y,newP->x+1)=='#' || mvinch(newP->y+1,newP->x)=='#' || mvinch(newP->y,newP->x-1)=='#' || mvinch(newP->y-1,newP->x)=='#'){
                attron(COLOR_PAIR(2));
                attron(A_BOLD);
                mvprintw(31,0,"   ^_^ You have left the room.");
                attroff(COLOR_PAIR(2));
                attroff(A_BOLD);
                //PMOVE(newP,user,level);
                refresh();
                time_t start_time=time(NULL);
                while(1){
                if(time(NULL)-start_time>=2){
                    
                    break;
                }
                }
                PMOVE(newP,user,level);
                break;
            }
            else{
                attron(COLOR_PAIR(2));
                attron(A_BOLD);
                mvprintw(31,0,"   ^_^ You have entered the room.");
                attroff(COLOR_PAIR(2));
                attroff(A_BOLD);
                refresh();
                time_t start_time=time(NULL);
                while(1){
                if(time(NULL)-start_time>=2){
                    
                    break;
                }
                }
                PMOVE(newP,user,level);
                break;
            }
        case '#':
            if(newP->y==level->rooms[3]->DOOR[0]->y-1 && newP->x==level->rooms[3]->DOOR[0]->x){
                Findroom[3]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if((newP->y==level->rooms[3]->DOOR[3]->y-1 && newP->x==level->rooms[3]->DOOR[3]->x+1)||(newP->y==level->rooms[3]->DOOR[3]->y+1 && newP->x==level->rooms[3]->DOOR[3]->x+1) || (newP->y==level->rooms[3]->DOOR[3]->y && newP->x==level->rooms[3]->DOOR[3]->x+1)){
                Findroom[3]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if((newP->y==level->rooms[4]->DOOR[2]->y-1 && newP->x==level->rooms[4]->DOOR[2]->x-1)||(newP->y==level->rooms[4]->DOOR[2]->y+1 && newP->x==level->rooms[4]->DOOR[2]->x-1) || (newP->y==level->rooms[4]->DOOR[2]->y && newP->x==level->rooms[4]->DOOR[2]->x-1)){
                Findroom[4]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if((newP->y==level->rooms[4]->DOOR[3]->y-1 && newP->x==level->rooms[4]->DOOR[3]->x+1)||(newP->y==level->rooms[4]->DOOR[3]->y+1 && newP->x==level->rooms[4]->DOOR[3]->x+1) || (newP->y==level->rooms[4]->DOOR[3]->y && newP->x==level->rooms[4]->DOOR[3]->x+1)){
                Findroom[4]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if((newP->y==level->rooms[1]->DOOR[2]->y-1 && newP->x==level->rooms[1]->DOOR[2]->x-1)||(newP->y==level->rooms[1]->DOOR[2]->y && newP->x==level->rooms[1]->DOOR[2]->x-1)||(newP->y==level->rooms[1]->DOOR[2]->y+1 && newP->x==level->rooms[1]->DOOR[2]->x-1)){
                Findroom[1]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if((newP->y==level->rooms[1]->DOOR[3]->y-1 && newP->x==level->rooms[1]->DOOR[3]->x+1)||(newP->y==level->rooms[1]->DOOR[3]->y && newP->x==level->rooms[1]->DOOR[3]->x+1)||(newP->y==level->rooms[1]->DOOR[3]->y+1 && newP->x==level->rooms[1]->DOOR[2]->x+1)){
                Findroom[1]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if((newP->y==level->rooms[5]->DOOR[2]->y-1 && newP->x==level->rooms[5]->DOOR[2]->x-1)||(newP->y==level->rooms[5]->DOOR[2]->y+1 && newP->x==level->rooms[5]->DOOR[2]->x-1) || (newP->y==level->rooms[5]->DOOR[2]->y && newP->x==level->rooms[5]->DOOR[2]->x-1)){
                Findroom[5]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if((newP->y==level->rooms[2]->DOOR[2]->y-1 && newP->x==level->rooms[2]->DOOR[2]->x-1)||(newP->y==level->rooms[2]->DOOR[2]->y && newP->x==level->rooms[2]->DOOR[2]->x-1)||(newP->y==level->rooms[2]->DOOR[2]->y+1 && newP->x==level->rooms[2]->DOOR[2]->x-1)){
                Findroom[2]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            if((newP->y==level->rooms[2]->DOOR[1]->y+1 && newP->x==level->rooms[2]->DOOR[1]->x)||(newP->y==level->rooms[2]->DOOR[1]->y+1 && newP->x==level->rooms[2]->DOOR[1]->x+1)||(newP->y==level->rooms[2]->DOOR[1]->y+1 && newP->x==level->rooms[2]->DOOR[1]->x-1)){
                Findroom[2]=1;
                DRAWROOM(level->rooms);
                level->tiles=LEVEL();
            }
            PMOVE(newP,user,level);
            break;
        case '>':
            clear();
            if(level->level==1){
                FILE * file=fopen("level1.txt","w");
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            fprintf(file,"%d ",map[i][j][k]);
                        }
                        fprintf(file,"\n");
                    }
                    fprintf(file,"\n");
                    fprintf(file,"\n");
                }
                fclose(file);
            }
            if(level->level==2){
                FILE * file=fopen("level2.txt","w");
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            fprintf(file,"%d ",map[i][j][k]);
                        }
                        fprintf(file,"\n");
                    }
                    fprintf(file,"\n");
                    fprintf(file,"\n");
                }
                fclose(file);
            }
            if(level->level==3){
                FILE * file=fopen("level3.txt","w");
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            fprintf(file,"%d ",map[i][j][k]);
                        }
                        fprintf(file,"\n");
                    }
                    fprintf(file,"\n");
                    fprintf(file,"\n");
                }
                fclose(file);
            }
            if(level->level==4){
                FILE * file=fopen("level4.txt","w");
                for(int i=0;i<4;i++){
                    for(int j=0;j<50;j++){
                        for(int k=0;k<200;k++){
                            fprintf(file,"%d ",map[i][j][k]);
                        }
                        fprintf(file,"\n");
                    }
                    fprintf(file,"\n");
                    fprintf(file,"\n");
                }
                fclose(file);
            }
            timerepet++;
            mainprim(timerepet);
            break;
        case '<':
            // attron(A_BLINK);
            // mvprintw(31,0,"   ^_^Enter <q>!");
            // attroff(A_BLINK);
            break;
        case 'f':
        case 'F':
        case 'Z':
        case 'A':
        case 'S':
        case 'z':
        case 'p':
        case 'G':
        case 'C':
        case 'x':
        case 'r':
        case 'v':
        case 't':
            PMOVE(newP,user,level);
            break;
        case '&':
            PMOVE(newP,user,level);
            pas=rand()%100+1100;
            init_pair(14,COLOR_BLUE,COLOR_WHITE);
            attron(COLOR_PAIR(14));
            attron(A_BLINK);
            mvprintw(32,3,"*_* PASSWORD %d",pas);
            attroff(COLOR_PAIR(14));
            attroff(A_BLINK);
            refresh();
            time_t start_time=time(NULL);
            while(1){
                if(time(NULL)-start_time>=30){
                    //move(32,3);
                }
            }
            move(32,3);
            clrtoeol();
            refresh();
            break;
            break;
        case '@':
            int PAS=0;
            mvprintw(40,0,"   ?PASSWORD ");
            //echo();
            refresh();
            //move(36,5);
            curs_set(0);
            scanw("%d",&PAS);
            refresh();
            echo();
            printw("%d",PAS);
            PMOVE(newP,user,level);
            break;
        case 'O':
            ENDSCREEN(level);
            break;
        case '^':
            user->health-=2;
            GAMELINE(level);
            break;
        case 'D':
            CONSUMEENEMY(user,0,level);
            init_pair(66,COLOR_BLACK,COLOR_RED);
            attron(COLOR_PAIR(66));
            attron(A_BOLD);
            mvprintw(31,3,"^_^ A DEMON has hurt you!");
            attroff(COLOR_PAIR(66));
            attroff(A_BOLD);
        case 'P':
            CONSUMEENEMY(user,1,level);
            init_pair(66,COLOR_BLACK,COLOR_RED);
            attron(COLOR_PAIR(66));
            attron(A_BOLD);
            mvprintw(31,3,"^_^ A FIRE BREATHING MOSTER has hurt you!");
            attroff(COLOR_PAIR(66));
            attroff(A_BOLD);
        default:
            move(user->position->y,user->position->x);
            break;
    }
    if(spell==3){
        if((hide_door_y==newP->y)&&(hide_door_x==newP->x)){
            mvprintw(newP->y,newP->x,"?");
            discover_hide_door=1;
            level->user->health-=1;
            GAMELINE(level);
        }
        if((hide_door_y1==newP->y)&&(hide_door_x1==newP->x)){
            mvprintw(newP->y,newP->x,"?");
            discover_hide_door1=1;
            level->user->health-=1;
            int room_number=get_room_number(user,level);
                if(room_number==0 || room_number==3 || room_number==5){
                    map[0][newP->y][newP->x]=13;
                }
                else if(room_number==1 || room_number==4){
                    map[2][newP->y][newP->x]=13;
                }
                else if(timerepet==4 && room_number==3){
                    map[3][newP->y][newP->x]=13;
                }
            GAMELINE(level);
        
        }
    }
    if(spell==2){
        if((hide_door_y_2_1==newP->y)&&(hide_door_x_2_1==newP->x)){
            mvprintw(newP->y,newP->x,"?");
            discover_hide_door_2_1=1;
            level->user->health-=1;
            int room_number=get_room_number(user,level);
                if(room_number==0 || room_number==3 || room_number==5){
                    map[0][newP->y][newP->x]=13;
                }
                else if(room_number==1 || room_number==4){
                    map[2][newP->y][newP->x]=13;
                }
                else if(timerepet==4 && room_number==3){
                    map[3][newP->y][newP->x]=13;
                }
            GAMELINE(level);
        }
        if((hide_door_y_2_2==newP->y)&&(hide_door_x_2_2==newP->x)){
            mvprintw(newP->y,newP->x,"?");
            discover_hide_door_2_2=1;
            level->user->health-=1;
            int room_number=get_room_number(user,level);
                if(room_number==0 || room_number==3 || room_number==5){
                    map[0][newP->y][newP->x]=13;
                }
                else if(room_number==1 || room_number==4){
                    map[2][newP->y][newP->x]=13;
                }
                else if(timerepet==4 && room_number==3){
                    map[3][newP->y][newP->x]=13;
                }
            GAMELINE(level);
        }
    }
    //}
    
    return 1;
}

int PMOVE(POSITION * newP,Player * user,LEVELs * level){
   
    level->nrooms=6;
    char buffer[80];
    if(level->tiles[user->position->y][user->position->x]!='$'){
        sprintf(buffer,"%c",level->tiles[user->position->y][user->position->x]);
        mvprintw(user->position->y,user->position->x,"%s",buffer);
    }
    else{
        mvprintw(user->position->y,user->position->x,".");
    }
    
    if(discover_hide_door){
        mvprintw(hide_door_y,hide_door_x,"?");
    }
    if(discover_hide_door1){
        mvprintw(hide_door_y1,hide_door_x1,"?");
    }
    if(discover_hide_door_2_2){
        mvprintw(hide_door_y_2_2,hide_door_x_2_2,"?");
    }
    if(discover_hide_door_2_1){
        mvprintw(hide_door_y_2_1,hide_door_x_2_1,"?");
    }


    user->position->x=newP->x;
    user->position->y=newP->y;

    mvprintw(user->position->y,user->position->x,"$");
    move(user->position->y,user->position->x);
    move(31,0);
    clrtoeol();
    
    return 1;

}

//TRAP
void TRAP(ROOM * room,int R){
    if(R==3){
        room->ntraps=rand()%4+1;
    }
    if(R==0){
        room->ntraps=rand()%2+1;
    }
    for(int i=0;i < room->ntraps;i++){
        int X=room->position.x+rand()%(room->width-2)+1;
        int Y=room->position.y+rand()%(room->height-2)+1;
        mvprintw(Y,X,".");
        trapplace[Y][X]=1;
        map[R][Y][X]=43;
    }
}

//FOOD
void PLACEFOODINROOM(ROOM * room){
    //srand(time(NULL));
    room->nfoods=rand()%3;
    room->foods=malloc(room->nfoods * sizeof(FOOD *));

    for(int i=0;i<room->nfoods;i++){
        room->foods[i]=malloc(sizeof(FOOD));
        //srand(time(NULL));
        room->foods[i]->food_type=rand()%4;
        room->foods[i]->timer=3;

    }
}
void UPDATEFOODS(ROOM  * room){
    for(int i=0;i<room->nfoods;i++){
        if(room->foods[i]->timer>0){
            room->foods[i]->timer--;
            if(room->foods[i]->timer==0){
                room->foods[i]->food_type=15;
            }
        }
    }
}
void CONSUMEFOOD(Player * user,int num,LEVELs * level){
    switch(num){
        case 0:
            user->health+=10;
            hunger+=2;
            break;
        case 1:
            user->health+=10;
            user->power+=5;
            hunger+=2;
            break;
        case 2:
            user->health+=10;
            user->speed+=1;
            hunger+=2;
            GAMELINE(level);
            break;
        case 3:
            user->health -=10;
            hunger--;
            break;
    }
    GAMELINE(level);
}
void DRAWFOOD(ROOM * room,int R){
    for(int i=0;i < room->nfoods;i++){
        int X=room->position.x+rand()%(room->width-2)+1;
        int Y=room->position.y+rand()%(room->height-2)+1;
        if(room->foods[i]->food_type==0){
            mvprintw(Y,X,"f");
            map[R][Y][X]=20;
        }
        else if(room->foods[i]->food_type==1){
            mvprintw(Y,X,"F");
            map[R][Y][X]=21;
        }
        else if(room->foods[i]->food_type==2){
            mvprintw(Y,X,"Z");
            map[R][Y][X]=22;
        }
        else if(room->foods[i]->food_type==3){
            mvprintw(Y,X,"f");
            map[R][Y][X]=20;
        }
    }
}
void EINPUT(Player * user,LEVELs * level){

        move(34,0);
        ROOM * current_room=get_current_room(user , level); 
        mvprintw(34,0,"%c",food_wehave[0]);
        mvprintw(34,2,"%c",food_wehave[1]);
        mvprintw(34,4,"%c",food_wehave[2]);
        mvprintw(34,6,"%c",food_wehave[3]);
        mvprintw(34,8,"%c",food_wehave[4]);
        
        draw_hunger_bar();
}
void draw_hunger_bar(){

    int bar=10;
    int filled=(hunger*bar)/max_huger;
    init_pair(7,COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    mvprintw(35,0,"   HUNGER: [");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(7));
    init_pair(8,COLOR_CYAN,COLOR_BLACK);
    attron(COLOR_PAIR(8));
    for(int i=0;i<filled;i++){
        printw("#");
    }
    for(int i=filled;i<bar;i++){
        printw(".");
    }
    attroff(COLOR_PAIR(8));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("]");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(7));

}
void update_hunger(LEVELs * level){

    static time_t lasttime=0;
    time_t currenttime=time(NULL);
    if(currenttime-lasttime >=10){
        hunger--;
        if(hunger<=0){
            level->user->health-=1;
        }
        lasttime=time(NULL);
        GAMELINE(level);
    }
    if(level->user->health<=0){
        clear();
        refresh();
        curs_set(0);
        init_pair(31,COLOR_RED,COLOR_BLACK);
        attron(COLOR_PAIR(31));
        attron(A_BLINK);
        attron(A_BOLD);
        move(20,50);
        mvprintw(20,60,"LOSERRRRRRRRRRRRRRRR");
        attroff(COLOR_PAIR(31));
        attroff(A_BLINK);
        attroff(A_BOLD);

    }
    
}

//GOLD
void PLACEFGOLDINROOM(ROOM * room){

    room->ngolds=rand()%2+1;
    room->golds=malloc(room->ngolds * sizeof(GOLD *));

    for(int i=0;i<room->ngolds;i++){
        room->golds[i]=malloc(sizeof(GOLD));
        room->golds[i]->gold_type=rand()%3;
    }
}
void CONSUMEGOLD(Player * user,int num,LEVELs * level){
    switch(num){
        case 0:
            user->gold+=2;
            user->score+=3;
            break;
        case 1:
            user->gold+=5;
            user->score+=9;
            break;
    }
    GAMELINE(level);
}
void DRAWGOLD(ROOM * room,int R){
    for(int i=0;i < room->ngolds;i++){
        int X=room->position.x+rand()%(room->width-2)+1;
        int Y=room->position.y+rand()%(room->height-2)+1;
        if(room->golds[i]->gold_type==0 || room->golds[i]->gold_type==1){
            init_pair(15,COLOR_BLACK,COLOR_YELLOW);
            attron(COLOR_PAIR(15));
            mvprintw(Y,X,"G");
            map[R][Y][X]=30;
            attroff(COLOR_PAIR(15));
        }
        else if(room->golds[i]->gold_type==2){
            init_pair(16,COLOR_BLACK,COLOR_CYAN);
            attron(COLOR_PAIR(16));
            mvprintw(Y,X,"C");
            map[R][Y][X]=31;
            attroff(COLOR_PAIR(16));
        }
    }
}

//SPELL
void PLACESPELLINROOM(ROOM * room,int Tabel){
    room->nspells=rand()%2;
    if(Tabel==1 || Tabel==4){
        room->nspells=rand()%4+3;
    }
    room->spells=malloc(room->nspells * sizeof(SPELL *));

    for(int i=0;i<room->nspells;i++){
        room->spells[i]=malloc(sizeof(SPELL));
        room->spells[i]->spell_type=rand()%3;
    }
}
void CONSUMESPELL(Player * user,int num,LEVELs * level){
    switch(num){
        case 0:
            movement=10;
            user->health+=2;
            GAMELINE(level);
            break;
        case 1:
            movement=10;
            user->speed+=2;
            GAMELINE(level);
            break;
        case 2:
            movement=10;
            break;
    }
    GAMELINE(level);
}
void DRAWSPELL(ROOM * room,int R){
    for(int i=0;i < room->nspells;i++){
        int X=room->position.x+rand()%(room->width-2)+1;
        int Y=room->position.y+rand()%(room->height-2)+1;
        if(room->spells[i]->spell_type==0){
            init_pair(40,COLOR_WHITE,COLOR_MAGENTA);
            attron(COLOR_PAIR(40));
            mvprintw(Y,X,"z");
            map[R][Y][X]=40;
            attroff(COLOR_PAIR(40));
        }
        else if(room->spells[i]->spell_type==1){
            init_pair(17,COLOR_BLUE,COLOR_MAGENTA);
            attron(COLOR_PAIR(17));
            mvprintw(Y,X,"S");
            map[R][Y][X]=41;
            attroff(COLOR_PAIR(17));
        }
        else if(room->spells[i]->spell_type==2){
            init_pair(18,COLOR_BLACK,COLOR_MAGENTA);
            attron(COLOR_PAIR(18));
            mvprintw(Y,X,"A");
            map[R][Y][X]=42;
            attroff(COLOR_PAIR(18));
        }
    }
}
void eINPUT(Player * user, LEVELs * level){
    move(37,0);
    init_pair(19,COLOR_MAGENTA,COLOR_BLACK);
    attron(COLOR_PAIR(19));
    attron(A_ITALIC);
    mvprintw(37,0,"   !HEALTH %d",spell_wehave_number[0]);
    printw("    !SPEED %d",spell_wehave_number[1]);
    printw("    !DAMAGE %d",spell_wehave_number[2]);
    attroff(COLOR_PAIR(19));
    attroff(A_ITALIC);
}

//WEAPON
void PLACEWEAPONINROOM(ROOM * room){
    room->nweapons=rand()%2+2;
    room->weapons=malloc(room->nweapons * sizeof(WEAPON *));

    for(int i=0;i<room->nweapons;i++){
        room->weapons[i]=malloc(sizeof(WEAPON));
        room->weapons[i]->weapon_type=rand()%4+1;
    }
}
void DRAWWEAPON(ROOM * room,int R){
    for(int i=0;i < room->nweapons;i++){
        int X=room->position.x+rand()%(room->width-2)+1;
        int Y=room->position.y+rand()%(room->height-2)+1;
        if(room->weapons[i]->weapon_type==0){
            init_pair(20,COLOR_WHITE,COLOR_BLUE);
            attron(COLOR_PAIR(20));
            mvprintw(Y,X,"p");
            map[R][Y][X]=50;
            attroff(COLOR_PAIR(20));
        }
        else if(room->weapons[i]->weapon_type==1){
            init_pair(21,COLOR_CYAN,COLOR_BLUE);
            attron(COLOR_PAIR(21));
            mvprintw(Y,X,"x");
            map[R][Y][X]=51;
            attroff(COLOR_PAIR(21));
        }
        else if(room->weapons[i]->weapon_type==2){
            init_pair(22,COLOR_GREEN,COLOR_BLUE);
            attron(COLOR_PAIR(22));
            mvprintw(Y,X,"r");
            map[R][Y][X]=52;
            attroff(COLOR_PAIR(22));
        }
        else if(room->weapons[i]->weapon_type==3){
            init_pair(23,COLOR_RED,COLOR_BLUE);
            attron(COLOR_PAIR(23));
            mvprintw(Y,X,"v");
            map[R][Y][X]=53;
            attroff(COLOR_PAIR(23));
        }
        else if(room->weapons[i]->weapon_type==4){
            init_pair(24,COLOR_BLACK,COLOR_BLUE);
            attron(COLOR_PAIR(24));
            mvprintw(Y,X,"t");
            map[R][Y][X]=54;
            attroff(COLOR_PAIR(24));
        }
    }
}
void iINPUT(Player * user, LEVELs * level){
    move(38,0);
    init_pair(25,COLOR_BLUE,COLOR_BLACK);
    init_pair(36,COLOR_YELLOW,COLOR_BLACK);
    attron(COLOR_PAIR(25));
    attron(A_ITALIC);
    mvprintw(38,0,"   *MACE p 5 1 %d",weapon_wehave_number[0]);
    attroff(COLOR_PAIR(25));
    attron(COLOR_PAIR(36));
    printw("    *DAGGER x 12 5 %d",weapon_wehave_number[1]);
    printw("    *MAGIC WAND r 15 10 %d",weapon_wehave_number[2]);
    printw("    *NORMAL ARROW v 5 5 %d",weapon_wehave_number[3]);
    attroff(COLOR_PAIR(36));
    attron(COLOR_PAIR(25));
    printw("    *SWORD t 10 1 %d",weapon_wehave_number[4]);
    attroff(COLOR_PAIR(25));
    attroff(A_ITALIC);
}
void CONSUMEWEAPON(Player * user,int num,LEVELs * level){

}
//ENEMY
// void moveENEMY(Player * user, ENEMY * e){
   

//     int dx=0;
//     int dy=0;

//     if(e->x < user->position->x){
//         dx=1;
//     }
//     else if(e->x > user->position->x){
//         dx=-1;
//     }

//     if(e->y < user->position->y){
//         dy=-1;
//     }
//     else if(e->y > user->position->y){
//         dy=1;
//     }

//     e->x+=dx;
//     e->x+=dy;

//     // if(e->follow_steps>0){
//     //     e->follow_steps--;
//     // }

// }
void PLACEENEMYINROOM(ROOM * room,int R){
    if(R==0){
        room->nenemies=rand()%2+2;
        room->enemies=malloc(room->nenemies * sizeof(ENEMY *));
        for(int i=0;i<room->nenemies;i++){
            room->enemies[i]=malloc(sizeof(ENEMY));
            room->enemies[i]->type=rand()%2;
        }
    }
    else if(R==3){
        room->nenemies=rand()%2+2;
        room->enemies=malloc(room->nenemies * sizeof(ENEMY *));
        for(int i=0;i<room->nenemies;i++){
            room->enemies[i]=malloc(sizeof(ENEMY));
            room->enemies[i]->type=rand()%2+2;
        }
    }
    else if(R==5){
        room->nenemies=rand()%2+1;
        room->enemies=malloc(room->nenemies * sizeof(ENEMY *));
        for(int i=0;i<room->nenemies;i++){
            room->enemies[i]=malloc(sizeof(ENEMY));
            room->enemies[i]->type=4;
        }
    }
}
void CONSUMEENEMY(Player * user,int num,LEVELs * level){
    switch(num){
        case 0:
            user->health-=1;
            user->score-=1;
            break;
        case 1:
            user->health-=3;
            break;
        case 2:
            user->health-=6;
            break;
        case 3:
            user->health-=7;
            break;
        case 4:
            user->health-=9;
    }
    GAMELINE(level);
}
void DRAWENEMY(ROOM * room,int R){
    for(int i=0;i < room->nenemies;i++){
        int X=room->position.x+rand()%(room->width-3)+1;
        int Y=room->position.y+rand()%(room->height-3)+1;
        attron(A_BOLD);
        init_pair(60,COLOR_BLACK,COLOR_RED);
        attron(COLOR_PAIR(60));
        if(room->enemies[i]->type==0){
            mvprintw(Y,X,"D");
            map[R][Y][X]=60;
        }
        attroff(COLOR_PAIR(60));
        init_pair(61,COLOR_CYAN,COLOR_RED);
        attron(COLOR_PAIR(61));
        if(room->enemies[i]->type==1){
            mvprintw(Y,X,"P");
            map[R][Y][X]=61;
        }
        attroff(COLOR_PAIR(61));
        init_pair(62,COLOR_WHITE,COLOR_RED);
        attron(COLOR_PAIR(62));
        if(room->enemies[i]->type==2){
            mvprintw(Y,X,"W");
            map[R][Y][X]=62;
        }
        attroff(COLOR_PAIR(62));
        init_pair(63,COLOR_GREEN,COLOR_RED);
        attron(COLOR_PAIR(63));
        if(room->enemies[i]->type==3){
            mvprintw(Y,X,"T");
            map[R][Y][X]=63;
        }
        attroff(COLOR_PAIR(63));
        init_pair(64,COLOR_BLUE,COLOR_RED);
        attron(COLOR_PAIR(64));
        if(room->enemies[i]->type==4){
            mvprintw(Y,X,"X");
            map[R][Y][X]=64;
        }
        attroff(COLOR_PAIR(64));
        attroff(A_BOLD);
    }
}
void MONSTERHIT(int weapon,int enemynumber,ROOM * room){
    if(weapon==0 && enemynumber==0){

    }
}



