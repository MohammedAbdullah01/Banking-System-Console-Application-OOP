#pragma once
#include <iostream>
#include "clsUser.h"

using namespace std;

string EmptyUsername = "", EmptyPassword = "";
clsUser CurrentUser = clsUser::Find(EmptyUsername, EmptyPassword);

