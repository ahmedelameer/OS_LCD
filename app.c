

#include"OS.h"
#include"LCD.h"


#define NUM_OF_QUESTIONS 5

void LCD_init_data(void);
void display_next_questions(void );
void CLear_After_3sec(void);
void GoToRowCol_1_0(void);

void display_next_ANS(void );

uint8_t DIS_QUS_REQUESTED=0;
uint8_t CleanIsReady=0;
static uint8_t FIRST_TIME=0;
static uint8_t NEXT_TIME=0;
static uint8_t lOCK_QUES=0;
static uint8_t lOCK_open=0;


uint8_t OPEN[]="READY!!!";

uint8_t QUES1[]="ARE U OK ?";
uint8_t QUES2[]="DO U EXCIST ?";
uint8_t QUES3[]="Joker ?";


uint8_t ANS1[]="2: NO?";
uint8_t ANS2[]="3:YES? 2:NO";
uint8_t ANS4[]="1: ARE U MAD NO!";
uint8_t ANS3[]="2: YES?";
uint8_t ANS6[]="NO";
uint8_t ANS7[]="NO U ARE NOT";




int main()
{
	DDRB=0xFF;
	PORTB=0;

	OS_ConfigType Config={2,Timer0};
	OS_ConfigType* ConfigPtr=&Config;



	OS_Init( ConfigPtr);

	OS_Creat_Task(1,LCD_init,0);


	OS_Creat_Task(100,LCD_init_data,1);

	OS_Creat_Task(1,LCD_display,2);

	OS_Creat_Task(1,LCD_gotoRawCol,3);

	OS_Creat_Task(2090,GoToRowCol_1_0,1);

	OS_Creat_Task(1,Clear_LCD,4);

	OS_Creat_Task(1950,CLear_After_3sec,3);

	OS_Creat_Task(2000,display_next_questions,5);

	OS_Creat_Task(2160,display_next_ANS,6);




	SREG|=(1<<7);

	OS_Run();
}


void LCD_init_data(void)
{

	if(LCD_CLEAR_REQUESTED==0)
	{
		if(LCD_Position_REQUESTED==0)
		{
			if(lOCK_open==0)
			{

				char_Ptr = OPEN;
				DIS_CHAR_REQUESTED=1;

				lOCK_open++;
				FIRST_TIME++;
				lOCK_QUES=0;
			}



		}

	}
}


void display_next_questions(void )
{
	if(lOCK_QUES==0)
	{
		if(LCD_Position_REQUESTED==0)
		{
			if(LCD_CLEAR_REQUESTED==0)
			{
				if(FIRST_TIME==1)
				{
					char_Ptr = QUES1;
					DIS_CHAR_REQUESTED=1;
					NEXT_TIME++;
					lOCK_QUES=1;

				}
				else if(FIRST_TIME==2)
				{

					char_Ptr = QUES2;
					DIS_CHAR_REQUESTED=1;
					NEXT_TIME++;
					lOCK_QUES=1;
				}
				else if(FIRST_TIME==3)
				{

					char_Ptr = QUES3;
					DIS_CHAR_REQUESTED=1;
					NEXT_TIME++;
					lOCK_QUES=1;
				}
			}
		}
	}
}

void display_next_ANS(void )
{
	if(lOCK_QUES==1)
	{
		if(LCD_Position_REQUESTED==0)

		{
			if(LCD_CLEAR_REQUESTED==0)
			{
				if(NEXT_TIME==1)
				{
					char_Ptr = ANS1;
					DIS_CHAR_REQUESTED=1;
					FIRST_TIME++;
					lOCK_QUES=0;


				}
				else if(NEXT_TIME==2)
				{

					char_Ptr = ANS2;
					DIS_CHAR_REQUESTED=1;
					FIRST_TIME++;
					lOCK_QUES=0;

				}
				else if(NEXT_TIME==3)
				{

					char_Ptr = ANS3;
					DIS_CHAR_REQUESTED=1;
					FIRST_TIME++;
					lOCK_QUES=0;

				}
			}
		}
	}
}

void CLear_After_3sec(void)
{
	LCD_CLEAR_REQUESTED=1;
	DIS_CHAR_REQUESTED=0;

}

void GoToRowCol_1_0(void)
{
	LCD_CLEAR_REQUESTED=0;
	DIS_CHAR_REQUESTED=0;
	LCD_Position_REQUESTED=1;

}
