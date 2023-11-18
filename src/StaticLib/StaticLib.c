#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include <stdlib.h>		// malloc, free
#include <stdbool.h>	// bool

#include "../include/lib_func.h"

// my_array を要素数nで初期化する
void initialize(my_array* ar, int n)
{
	if (ar == NULL) return;// NULLチェック

	if (n <= 0) { // 非正の値が来たら、とりあえず空にする
		ar->num = 0;
		ar->addr = NULL;
		return;
	}

	ar->num = n;
	ar->addr = (int*)malloc(sizeof(int) * n);

	// 確保できなかったら要素数は0とする
	if (ar->addr == NULL) ar->num = 0;
}

// my_array を解放する
void release(my_array* ar)
{
	free(ar->addr);
	ar->addr = NULL;// 多重解放の防止
}

// my_array の要素数を変更する(以前の値は要素が同じ範囲で残す)
void resize(my_array* ar, int n)
{
	int copy_ar_num=ar->num;
	int* copy_ar_addr; int resize_num = 0;
	if (copy_ar_num <= 0)
	{
		copy_ar_num = 0;
		copy_ar_addr = NULL;
		return;
	}
	copy_ar_addr = (int*)malloc(sizeof(int) * copy_ar_num);
	if (copy_ar_addr == NULL)return;
	if (copy_ar_addr == NULL) {
		copy_ar_num = 0;
	}

	for (int i = 0; i <= copy_ar_num; i++)
	{
		if (ar->addr != NULL) 
		{
			copy_ar_addr[i-1] = ar->addr[i-1];
		}
	}
	ar->num = n;
	ar->addr = (int*)malloc(sizeof(int) * n);
	if (ar->addr == NULL)return;

	if (ar->num > copy_ar_num)
		resize_num = copy_ar_num;
	else if (ar->num < copy_ar_num)
		resize_num = ar->num;
	for (int i = 0; i <= resize_num; i++)
	{
		if (copy_ar_addr != NULL)
			ar->addr[i-1] = copy_ar_addr[i-1];
	}
	free(copy_ar_addr);
	copy_ar_addr = NULL;
}
// my_array のindex番目の要素にvalを設定する
// index が確保されていない場所を指していたら返り値をfalseにする（設定出来たらtrue）
bool set(my_array* ar, int index, int val)
{
	// ToOo:配列の要素を変更しよう！
	if (index > ar->num-1 || index < 0)
		return false;
	
	ar->addr[index] = val;
	return true;
}

// my_array のindex番目の要素を取得する
// index が確保されていない場所を指していたら0を返す
int get(const my_array* ar, int index)
{
	//ToOo:要素を所得して、indexがおかしかったら0を返そう
	if (index < 0 || index > ar->num-1)
		return 0;
	else
		return ar->addr[index];
}

// my_array の要素数を取得する
int size(const my_array* ar)
{
	// ToOo: 配列の要素数を返そう
	
	return ar->num;
}