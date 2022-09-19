#pragma once

#include <gtest/gtest.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int get_answer(int elem);
int get_result(int elem);


int get_result(int elem)
{
	static int array[5] = {0};
	static int flag = 0;
	FILE *results;
	if (flag == 0)
	{
		flag++;
		results = fopen("results.txt", "r");
  		
    	for (int i = 0; i < 5; i++)
    	{
      		fscanf(results, "%d", &array[i]);
    	}
    
    	fclose(results);
    	return array[elem];
  	}
	else
	{
		return array[elem];
	}

}

int get_answer(int elem)
{
	static int array[5] = {0};
	static int flag = 0;
	FILE *results;
	if (flag == 0)
	{
		flag++;
		results = fopen("answers.txt", "r");
  		
    	for (int i = 0; i < 5; i++)
    	{
      		fscanf(results, "%d", &array[i]);
    	}
    
    	fclose(results);
    	
    	return array[elem];
  	}
	else
	{
		return array[elem];
	}

}

