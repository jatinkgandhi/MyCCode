/* Fix Menu Options Solution For Embedded Target*/	
/* This code can be re-factored to be made more elegant */

#include <stdio.h>

/* Menu Code */
#define MAX_OPTION_NAME_LEN	(unsigned int)(8)

typedef struct _OPTION_T
{
	char Name[MAX_OPTION_NAME_LEN];
	void (*OnClick)(void);
}Option;

#define MAX_OPTIONS	(unsigned int)(10)

typedef struct _MENU_T
{
	Option Options[MAX_OPTIONS];
	unsigned int TotalOptions;
	unsigned int Current;
}Menu;

void ShowMenu(Menu *menu)
{
	int index;
	if((NULL == menu) || (menu->TotalOptions > MAX_OPTIONS))
	{
		return;
	}

	for(index = 0; index < menu->TotalOptions; index++)
	{
		printf("[%s]\n",menu->Options[index].Name);
	}
}

void UnShow(Option *option)
{
	if(NULL != option)
	{
		printf("[%s]\n",option->Name);
	}
}

void Show(Option *option)
{
	if(NULL != option)
	{
		printf(">> %s\n",option->Name);
	}
}
void MenuNavigateDown(Menu *menu)
{
	if(NULL == menu)
	{
		return;
	}
	
	if(menu->Current < (menu->TotalOptions - 1))
	{
		UnShow( &(menu->Options[menu->Current]));
		menu->Current++;
		Show( &(menu->Options[menu->Current]));
	}
}

void OnClick(Option *option)
{
	if( (NULL != option)  && (NULL != option->OnClick))
	{
		option->OnClick();
	}
}


void MenuNavigateUp(Menu *menu)
{
	if(NULL == menu)
	{
		return;
	}
	
	if(0 != menu->Current)
	{
		Show( &(menu->Options[menu->Current - 1]));
		UnShow( &(menu->Options[menu->Current]));
		menu->Current--;

	}
}
/* Test Code */
void Option_1_OnClick(void)
{
	printf("%s()\n",__func__);
}

void Option_2_OnClick(void)
{
	printf("%s()\n",__func__);
}

void Option_3_OnClick(void)
{
	printf("%s()\n",__func__);
}


int main(int argc, char **argv)
{
	Menu m;
	
	strncpy(m.Options[0].Name,"First",MAX_OPTION_NAME_LEN);
	m.Options[0].OnClick = Option_1_OnClick;
	
	
	strncpy(m.Options[1].Name,"Second",MAX_OPTION_NAME_LEN);
	m.Options[1].OnClick = Option_2_OnClick;
	
	
	strncpy(m.Options[2].Name,"Third",MAX_OPTION_NAME_LEN);
	m.Options[2].OnClick = Option_3_OnClick;
	
	m.TotalOptions = 3;
	m.Current      = 0;

	ShowMenu(&m);

	sleep(1);
	MenuNavigateDown(&m);
	OnClick(&(m.Options[m.Current]));
	sleep(1);
	MenuNavigateDown(&m);

	OnClick(&(m.Options[m.Current]));
	sleep(1);
	MenuNavigateDown(&m);
	sleep(1);
	OnClick(&(m.Options[m.Current]));
	MenuNavigateUp(&m);
	sleep(1);
	MenuNavigateUp(&m);
	OnClick(&(m.Options[m.Current]));
	sleep(1);
	MenuNavigateDown(&m);
	sleep(1);
	return 0;
}


