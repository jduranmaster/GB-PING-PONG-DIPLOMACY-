//*****************************************
//	Ping Pong Diplomacy for GameBoy.
// Programmed by jduranmaster a.k.a. Ryoga
//*****************************************

#include <gb/gb.h>
#include <stdio.h>
#include <ctype.h>
#include <gb/console.h>
#include <gb/drawing.h>

#include "images/_blank_text.h"
#include "images/x_congrats_win.h"
#include "images/hammer_keyboard_.h"
#include "images/x_production_first.h"
#include "images/x_production_second.h"
#include "images/x_pongdiplomacy_logo.h"

static const unsigned char TEXT_cEMPTY[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char backgroundcharacters[] = {
	//esquina superior izquierda
	0xFF,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	//esquina superior derecha
	0xFF,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	//esquina inferior izquierda
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0xFF,0xFF,0xFF,0xFF,
	//esquina inferior derecha
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	0x03,0x03,0x03,0x03,0xFF,0xFF,0xFF,0xFF,
	//pared de arriba
	0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	//pared derecha
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	//pared de abajo
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
	//pared izquierda
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	//relleno
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
}; 

signed char spritetiles[] = {
	//paddle
	255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,
	//bola
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	//null
	0x00,0x00,0x18,0x18,0x24,0x24,0x24,0x24,
	0x24,0x24,0x24,0x24,0x18,0x18,0x00,0x00,
	//1
	0x00,0x00,0x08,0x08,0x18,0x18,0x28,0x28,
	0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
	//2
	0x00,0x00,0x18,0x18,0x24,0x24,0x08,0x08,
	0x10,0x10,0x20,0x20,0x3C,0x3C,0x00,0x00,
	//3
	0x38,0x38,0x04,0x04,0x04,0x04,0x38,0x38,
	0x04,0x04,0x04,0x04,0x38,0x38,0x00,0x00,
	//4
	0x08,0x08,0x10,0x10,0x20,0x20,0x48,0x48,
	0x7C,0x7C,0x08,0x08,0x08,0x08,0x00,0x00,
	//5
	0x00,0x00,0x3C,0x3C,0x20,0x20,0x38,0x38,
	0x04,0x04,0x04,0x04,0x38,0x38,0x00,0x00,
	//6
	0x00,0x00,0x1C,0x1C,0x20,0x20,0x20,0x20,
	0x3C,0x3C,0x24,0x24,0x3C,0x3C,0x00,0x00,
	//7
	0x00,0x00,0x3C,0x3C,0x04,0x04,0x08,0x08,
	0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	//8
	0x18,0x18,0x24,0x24,0x24,0x24,0x18,0x18,
	0x24,0x24,0x24,0x24,0x18,0x18,0x00,0x00,
	//9
	0x18,0x18,0x24,0x24,0x24,0x24,0x1C,0x1C,
	0x04,0x04,0x04,0x04,0x18,0x18,0x00,0x00,
	//10
	0x26,0x26,0x69,0x69,0xA9,0xA9,0x29,0x29,
	0x29,0x29,0x29,0x29,0x26,0x26,0x00,0x00
};

signed char collision_left_up[] = {
	3,-1,1,0,
	3,-1,1,0,
	3,-1,1,0,
	3,-1,1,0,
	//--
	3,-1,2,-1,
	3,-1,2,-1,
	3,-1,2,-1,
	3,-1,2,-1,
	//--
	3,-2,2,-1,
	3,-2,2,-1,
	3,-2,2,-1,
	3,-2,2,-1,
	//--
	3,-2,2,-1,
	3,-2,2,-1,
	3,-2,2,-1,
	3,-2,2,-1
};

signed char collision_left_down[] = {
	3,1,1,0,
	3,1,1,0,
	3,1,1,0,
	3,1,1,0,
	//--
	3,1,2,1,
	3,1,2,1,
	3,1,2,1,
	3,1,2,1,
	//--
	3,2,2,1,
	3,2,2,1,
	3,2,2,1,
	3,2,2,1,
	//--
	3,2,3,1,
	3,2,3,1,
	3,2,3,1,
	3,2,3,1
};

signed char collision_right_up[] =  {
	-3,-1,-1,0,
	-3,-1,-1,0,
	-3,-1,-1,0,
	-3,-1,-1,0,
	//--
	-3,-1,-2,-1,
	-3,-1,-2,-1,
	-3,-1,-2,-1,
	-3,-1,-2,-1,
	//--
	-3,-2,-2,-1,
	-3,-2,-2,-1,
	-3,-2,-2,-1,
	-3,-2,-2,-1,
	//--
	-3,-2,-3,-1,
	-3,-2,-3,-1,
	-3,-2,-3,-1,
	-3,-2,-3,-1
};

signed char collision_right_down[] = {
	-3,1,-1,0,
	-3,1,-1,0,
	-3,1,-1,0,
	-3,1,-1,0,
	//--
	-3,1,-2,1,
	-3,1,-2,1,
	-3,1,-2,1,
	-3,1,-2,1,
	//--
	-3,2,-2,1,
	-3,2,-2,1,
	-3,2,-2,1,
	-3,2,-2,1,
	//--
	-3,2,-3,1,
	-3,2,-3,1,
	-3,2,-3,1,
	-3,2,-3,1
};
	
signed char bgmap[] = {
	//bgmap
	0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1,
	7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,5,
	2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,3,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
};

//variables globales del programa.
UBYTE counter,y1,y2,y3,y4,y5,y6;
UBYTE ball_pos_x;
UBYTE ball_pos_y;
BYTE ball_vector_x1;
BYTE ball_vector_x2;
BYTE ball_vector_y1;
BYTE ball_vector_y2;
UBYTE vector_pointer;
UBYTE game_status;
UBYTE colx;
UBYTE coly;
BYTE temp1;
BYTE temp2;
UBYTE col0;
UBYTE col1;
BYTE* col_table;
BYTE score_p1;
BYTE score_p2;
BYTE score_counter_p1;
BYTE score_counter_p2;
int controller = 0;

// variables de control del texto.
UBYTE tile_offset = 1;
UBYTE tile_height = 18;

// funciones del programa.
void RESET_TENNIS_COURT_BACKGROUND(void);
void RESET_COORDS();
void CLEAR_SCREEN_TEXT();
void PRINT_SOLID_MARQUEE();
void PLOT_SET_BACKGROUND_LOGO();
void CLEAR_SCREEN_LINE (UBYTE y);
void CLEAR_SCREEN_BACKGROUND(void);
void PLAY_PADDLE_SOUND_EFFECT(void);
void PLAY_UL_WALL_SOUND_EFFECT(void);
void PLAY_LR_WALL_SOUND_EFFECT(void);
void INIT_REGISTERS_SOUND_EFECTS(void);
void PRINT_MESSAGE(int x, int y, char *c);
UBYTE CHECK_COLLISION_BALL_PADDLE(UBYTE paddleNr);
void PLOT_BACKGROUND_IMAGE(int coord_X, int coord_Y, int tam_tile_X, int tam_tile_Y, unsigned char *tile_data, unsigned char *map_data, int millis);

void main(){
	PLOT_SET_BACKGROUND_LOGO();
	PLOT_BACKGROUND_IMAGE(0, 0, 20, 18, x_pongdiplomacy_logo_tile_data, x_pongdiplomacy_logo_map_data, 2000);
	waitpad(J_START);
	
	///// COMIENZA EL BLOQUE BITMAP DONDE SE MUESTRA EL TEXTO DEL JUEGO.
	PLOT_BACKGROUND_IMAGE(0, 0, 20, 18, _blank_text_tile_data, _blank_text_map_data, 2000);
	waitpad(J_START);
	///// TERMINA EL BLOQUE BITMAP DONDE SE MUESTRA EL TEXTO DEL JUEGO.
	
	disable_interrupts();
	DISPLAY_OFF;
	
	RESET_COORDS();
	
	//fijar las puntuaciones a cero.
	score_p1 = 0;
	score_p2 = 0;
	score_counter_p1 = 0;
	score_counter_p2 = 0;

	//background
	set_bkg_data(0,10,backgroundcharacters);
	//background
	set_bkg_tiles(0, 0, 20, 1, bgmap);
	//background
	for(counter=1;counter<=13;counter++) set_bkg_tiles(0,counter,20,1,bgmap+20);
	set_bkg_tiles(0,14,20,1,bgmap+40);
	
	for(counter=15;counter<=17;counter++) set_bkg_tiles(0,counter,20,1,bgmap+20);
	set_bkg_tiles(0,14,20,1,bgmap+40);
	
	//cargar los sprites.
	SPRITES_8x8;
	//cargar los tiles del paddle.
	set_sprite_data(0, 1, spritetiles);
	//cargar los tiles de la bola.
	set_sprite_data(1, 1, spritetiles+16);
	//cargar los tiles de las puntuaciones.
	set_sprite_data(2, 1, spritetiles+32);
	set_sprite_data(3, 1, spritetiles+48);
	set_sprite_data(4, 1, spritetiles+64);
	set_sprite_data(5, 1, spritetiles+80);
	set_sprite_data(6, 1, spritetiles+96);
	set_sprite_data(7, 1, spritetiles+112);
	set_sprite_data(8, 1, spritetiles+128);
	set_sprite_data(9, 1, spritetiles+144);
	set_sprite_data(10, 1, spritetiles+160);
	set_sprite_data(11, 1, spritetiles+176);
	set_sprite_data(12, 1, spritetiles+192);
	
	//paddle 0. Controlada por el usuario. [China].
	set_sprite_tile(0,0);
	set_sprite_tile(1,0);
	set_sprite_tile(2,0);
	
	//paddle 1. Controlado por la CPU. [USA].
	set_sprite_tile(3,0);
	set_sprite_tile(4,0);
	set_sprite_tile(5,0);
	//bola.
	set_sprite_tile(6,1);
	
	//activar fondos y sprites.
	SHOW_BKG;
	SHOW_SPRITES; 
	DISPLAY_ON;
	enable_interrupts();
	
	INIT_REGISTERS_SOUND_EFECTS();
	
	//Control del programa.
	while(1) {
		wait_vbl_done();

		set_sprite_tile(7,2+score_counter_p1);
		set_sprite_tile(8,2+score_counter_p2);
		
		if((score_p1 == 10 || score_p2 == 10) || controller == 1){
			if((score_counter_p2 == 10 || score_counter_p1 == 10)){
				HIDE_SPRITES;
				PLOT_BACKGROUND_IMAGE(0, 0, 20, 18, x_congrats_win_tile_data, x_congrats_win_map_data, 1000);
				waitpad(J_START);
				CLEAR_SCREEN_BACKGROUND();
				RESET_COORDS();
				controller = 0;
			}
			
			if(controller == 1){
				score_p1 = 0;
				score_p2 = 0;
				set_sprite_tile(7,2+score_counter_p1);
				set_sprite_tile(8,2+score_counter_p2);
			}else{
				score_p1 = 0;
				score_p2 = 0;
				score_counter_p1 = 0;
				score_counter_p2 = 0;
				ball_vector_x1 = 1;
				ball_vector_x2 = 1;
				ball_vector_y1 = 1;
				ball_vector_y2 = 1;
				
				set_bkg_data(0,10,backgroundcharacters);
				set_bkg_tiles(0, 0, 20, 1, bgmap);
				for(counter=1;counter<=13;counter++) set_bkg_tiles(0,counter,20,1,bgmap+20);
				set_bkg_tiles(0,14,20,1,bgmap+40);
				for(counter=15;counter<=17;counter++) set_bkg_tiles(0,counter,20,1,bgmap+20);
				set_bkg_tiles(0,14,20,1,bgmap+40);
				
				SPRITES_8x8;
				set_sprite_data(0, 1, spritetiles);
				set_sprite_data(1, 1, spritetiles+16);
				set_sprite_data(2, 1, spritetiles+32);
				set_sprite_data(3, 1, spritetiles+48);
				set_sprite_data(4, 1, spritetiles+64);
				set_sprite_data(5, 1, spritetiles+80);
				set_sprite_data(6, 1, spritetiles+96);
				set_sprite_data(7, 1, spritetiles+112);
				set_sprite_data(8, 1, spritetiles+128);
				set_sprite_data(9, 1, spritetiles+144);
				set_sprite_data(10, 1, spritetiles+160);
				set_sprite_data(11, 1, spritetiles+176);
				set_sprite_data(12, 1, spritetiles+192);
				SHOW_SPRITES;
				game_status = 1;
				controller = 0;
			}
		}
		
		counter = joypad();
		
		// movimiento del paddle 0.
		if(counter & J_UP && y1>=20){
			y1-=1;
			y2-=1;
			y3-=1;
			if(CHECK_COLLISION_BALL_PADDLE(0)<16){
				y1+=1;
				y2+=1;
				y3+=1;
			}
		}
		if(counter & J_DOWN && y3<=124){
			y1+=1;
			y2+=1;
			y3+=1;
			if(CHECK_COLLISION_BALL_PADDLE(0)<16){
				y1-=1;
				y2-=1;
				y3-=1;
			}
		}

		// movimiento del paddle 1.
		if(y5 > ball_pos_y && y4 >= 20){
			y4-=1;
			y5-=1;
			y6-=1;
			if(CHECK_COLLISION_BALL_PADDLE(1)<16){
				y4+=1;
				y5+=1;
				y6+=1;
			}
		}
		if(y5 < ball_pos_y && y6 <= 124){
			y4+=1;
			y5+=1;
			y6+=1;
			if(CHECK_COLLISION_BALL_PADDLE(1)<16){
				y4-=1;
				y5-=1;
				y6-=1;
			}
		}

		if(counter & J_START && game_status==0){
			//si el juego ha terminado, se reinicia.
			if(score_counter_p2 == 10 || score_counter_p1 == 10){
				score_p1 = 0;
				score_p2 = 0;
				score_counter_p2 = 0;
				score_counter_p1 = 0;
			}
			ball_vector_x1 = 1;
			ball_vector_x2 = 1;
			ball_vector_y1 = 1;
			ball_vector_y2 = 1;
			game_status = 1; //el juego comienza de nuevo.
		}
		
		// movimiento de la bola.
		if(vector_pointer==0){
			temp1 = ball_vector_x1;
			temp2 = ball_vector_y1;
			vector_pointer = 1;
		}
		else{
			temp1 = ball_vector_x2;
			temp2 = ball_vector_y2;
			vector_pointer = 0;
		}
		ball_pos_x+=temp1;
		ball_pos_y+=temp2;
		col0=CHECK_COLLISION_BALL_PADDLE(0);
		if(col0<16){
			while(temp1!=0 || temp2!=0){
				if(temp1>0){
					temp1--;
					ball_pos_x--;
				}
				if(temp1<0){
					temp1++;
					ball_pos_x++;
				}
				if(temp2>0){
					temp2--;
					ball_pos_y--;
				}
				if(temp2<0){
					temp2++;
					ball_pos_y++;
				}
				if (CHECK_COLLISION_BALL_PADDLE(0)>=16) break;
			}
			PLAY_PADDLE_SOUND_EFFECT();
		}
		
		col1=CHECK_COLLISION_BALL_PADDLE(1);
		if (col1 < 16){
			while(temp1!=0 || temp2!=0){
				if(temp1 > 0){
					temp1--;
					ball_pos_x--;
				}
				if(temp1 < 0){
					temp1++;
					ball_pos_x++;
				}
				if(temp2 > 0){
					temp2--;
					ball_pos_y--;
				}
				if(temp2 < 0){
					temp2++;
					ball_pos_y++;
				}
				if (CHECK_COLLISION_BALL_PADDLE(1)>=16) break;
			}
			PLAY_PADDLE_SOUND_EFFECT();
		}

		// detección de colisiones.
		// pared izquierda.
		if(ball_pos_x<9){
			RESET_COORDS();
			score_p2++;
			PLAY_UL_WALL_SOUND_EFFECT();
			score_counter_p2++;
			//el jugador 2 anota un tanto.
			controller = 1;
		}
		// pared derecha.
		if(ball_pos_x>163){
			RESET_COORDS();
			score_p1++;
			score_counter_p1++;
			PLAY_UL_WALL_SOUND_EFFECT();
			//el jugador 1 anota un tanto.
			controller = 1;
		}
		
		// pared superior.
		if(ball_pos_y < 19){
			ball_pos_y = 19;
			ball_vector_y1--;
			ball_vector_y1=ball_vector_y1 ^ 255;
			ball_vector_y2--;
			ball_vector_y2=ball_vector_y2 ^ 255;
			PLAY_LR_WALL_SOUND_EFFECT();
		}
		
		// pared inferior.
		if(ball_pos_y > 125){
			ball_pos_y = 125;
			ball_vector_y1--;
			ball_vector_y1=ball_vector_y1 ^ 255;
			ball_vector_y2--;
			ball_vector_y2=ball_vector_y2 ^ 255;
			PLAY_LR_WALL_SOUND_EFFECT();
		}
		
		if(col0<16 && ball_pos_x == 23){
			// la bola se desplaza arriba.
			if(ball_vector_y1<0 || ball_vector_y2<0) col_table = &collision_left_up;
			// la bola se desplaza abajo.
			else col_table = &collision_left_down;
			col_table+=col0*4;
			ball_vector_x1 = *col_table;
			ball_vector_y1 = *(col_table+1);
			ball_vector_x2 = *(col_table+2);
			ball_vector_y2 = *(col_table+3);
		}

		if(col1<16 && ball_pos_x==145){
			// la bola se desplaza arriba.
			if(ball_vector_y1<0 || ball_vector_y2<0) col_table = &collision_right_up;
			// la bola se desplaza abajo.
			else col_table = &collision_right_down;
			col_table+=col1*4;
			ball_vector_x1 = *col_table;
			ball_vector_y1 = *(col_table+1);
			ball_vector_x2 = *(col_table+2);
			ball_vector_y2 = *(col_table+3);
		}

		//caso especial col0
		if(col0<16 && ball_pos_x!=23){
			ball_vector_y1--;
			ball_vector_y2--;
			ball_vector_y1=ball_vector_y1^255;
			ball_vector_y2=ball_vector_y2^255;
		}

		//caso especial col1
		if(col1<16 && ball_pos_x!=145){
			ball_vector_y1--;
			ball_vector_y2--;
			ball_vector_y1=ball_vector_y1^255;
			ball_vector_y2=ball_vector_y2^255;
		}

		//repintar sprite del paddle0 en función de su posición actual.
		move_sprite(0,15,y1);
		move_sprite(1,15,y2);
		move_sprite(2,15,y3);
		//repintar sprite del paddle1 en función de su posición actual.
		move_sprite(3,153,y4);
		move_sprite(4,153,y5);
		move_sprite(5,153,y6);
		////repintar bola en función de su posición actual.
		move_sprite(6,ball_pos_x,ball_pos_y);
		//repintar puntuaciones.
		move_sprite(7,15,140);
		move_sprite(8,153,140);
	}
}

void PLOT_BACKGROUND_IMAGE(int coord_X, int coord_Y, int tam_tile_X, int tam_tile_Y, unsigned char *tile_data, unsigned char *map_data, int millis){
	set_bkg_data(coord_X, coord_Y, tile_data);
	set_bkg_tiles(coord_X, coord_Y, tam_tile_X, tam_tile_Y, map_data);
	SHOW_BKG;
	DISPLAY_ON;
	delay(millis);
}

void PLOT_SET_BACKGROUND_LOGO(){
	PLOT_BACKGROUND_IMAGE(0, 0, 20, 18, x_production_first_tile_data, x_production_first_map_data, 2000);
	CLEAR_SCREEN_BACKGROUND();
	PLOT_BACKGROUND_IMAGE(0, 0, 20, 18, hammer_keyboard__tile_data, hammer_keyboard__map_data, 2000);
	CLEAR_SCREEN_BACKGROUND();
	PLOT_BACKGROUND_IMAGE(0, 0, 20, 18, x_production_second_tile_data, x_production_second_map_data, 2000);
	CLEAR_SCREEN_BACKGROUND();
}

void PRINT_SOLID_MARQUEE(){
	gotoxy(0, 0);
	color(BLACK, WHITE, SOLID);
	box(156,140,2,2,M_NOFILL);
	box(155,139,3,3,M_NOFILL);
	box(154,138,4,4,M_NOFILL);
	box(153,137,5,5,M_NOFILL);
	box(152,136,6,6,M_NOFILL);
}

void INIT_REGISTERS_SOUND_EFECTS(void){
	NR52_REG = 0xF8U;
	NR51_REG = 0x00U;
	NR50_REG = 0x77U;//0xFFU;
}

void PLAY_PADDLE_SOUND_EFFECT(void){
    NR10_REG = 0x34U;
	NR11_REG = 0x80U;
	NR12_REG = 0xF0U;
	NR13_REG = 0x0AU;
	NR14_REG = 0xC6U;
	NR51_REG |= 0x11;
}

void PLAY_UL_WALL_SOUND_EFFECT(void){
    NR41_REG = 0x00;//0x1FU;
    NR42_REG = 0xE1;//0xF7U;
    NR43_REG = 0x22;//0x24U;
    NR44_REG = 0xC3;//0x80U;
    NR51_REG = 0x88U;
}

void PLAY_LR_WALL_SOUND_EFFECT(void){
	NR10_REG = 0x04U;
	NR11_REG = 0xFEU;
	NR12_REG = 0xA1U;
	NR13_REG = 0x8FU;
	NR14_REG = 0x86U;
	NR51_REG = 0xF7;
}

void RESET_COORDS(){
	//pos inicial paddle0.
	y1 = 65;
	y2 = 73;
	y3 = 81;
	//pos inicial paddle1.
	y4 = 65;
	y5 = 73;
	y6 = 81;
	//pos inicial bola.
	ball_pos_x=80;
	ball_pos_y=77;
	//inicializar el vector de movimiento.
	ball_vector_x1 = 0;
	ball_vector_x2 = 0;
	ball_vector_y1 = 0;
	ball_vector_y2 = 0;
	vector_pointer = 0;
	
	// juego en pausa.
	game_status = 0;
	return;
}

UBYTE CHECK_COLLISION_BALL_PADDLE(UBYTE paddleNr){
	//paddle0
	if(paddleNr==0){
		if(ball_pos_x>=15) 
			colx = ball_pos_x - 15;	
		else 
			colx = 15 - ball_pos_x;
		if (colx<8){
			//from x point of view there might be a collision
			if (ball_pos_y >= y2) coly = ball_pos_y - y2;
			else coly = y2 - ball_pos_y;
			//check the y point of view
			return coly;
		}
		return 16;
	}
	//paddle1
	else{
		
		if(ball_pos_x>=153)
			colx = ball_pos_x - 153;
		else
			colx = 153 - ball_pos_x;
		if (colx<8){
			//from x point of view there might be a collision
			if (ball_pos_y >= y5) coly = ball_pos_y - y5;
			else coly = y5 - ball_pos_y;
			//check the y point of view
			return coly;
		}
		return 16;
	}
}

void PRINT_MESSAGE(int x, int y, char *c){
	gotogxy(x,y);
	gprintf(c);
}

void CLEAR_SCREEN_LINE ( UBYTE y ){
	UBYTE x;
	for (x = y*20 ; x < (y+1)*20 ; x++ ){
    	set_bkg_data (x+tile_offset,1,(unsigned char *)TEXT_cEMPTY);
  	}
}

void CLEAR_SCREEN_BACKGROUND ( void ){
	UBYTE x;
	for ( x = 0 ; x < tile_height ; x++ ){
    	CLEAR_SCREEN_LINE ( x );
  	}
}

void CLEAR_SCREEN_TEXT(){
	int x, y;
	
  	for(y = 0; y < 20; y++){
    	for(x = 0; x < 30; x++){
      		gotoxy(x, y);
      		gprintf(" ");
		}
	}
	gotoxy(0,0);
}