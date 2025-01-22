#include <iostream>
#include "Global.h"  
#include "clsDate.h"
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsLoginScreen.h"
#include "clsMainMenueScreen.h"

using namespace std;



int main()
{
	
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}
}