#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void);

int main(void)
{
	int siiresu[14], karisiire;		//仕入れ数
	//int siiregaku[14];			//仕入れ額
	int tanka[14];					//販売単価
	int hambaisu[14];				//販売数
	int prevhambaisu[14];			//前の取引までの販売数
	int jumbikin, sougaku, aridaka, siire, kyaku, no;		//会計管理
	int code, kosu, tensuu, goukei, azukari;				//販売処理
	int confirm, roop, codeerror, deletetype;				//システム
	int i, n;
	char buffer[256];
	char command;
	char disp[50];
	FILE *log, *log2, *log3;
	errno_t err, err2, err3;


	//落ちた場合の復旧はurilog.txtのデータをhambaisu[i],sougaku,kyaku,noに，
	//siiresuhenkoulog.txtのデータをsiiresu[i],siireに打ち込んで営業を再開します．


	//仕入れ数入力(1日当たり)
	siiresu[0] = 120;		//おにぎり（鮭）
	siiresu[1] = 120;		//おにぎり（明太子）
	siiresu[2] = 120;		//おにぎり（ツナマヨ）
	siiresu[3] = 120;		//おにぎり（黒豚焼肉）
	siiresu[4] = 80;		//冷やし中華
	siiresu[5] = 120;		//ウーロン茶
	siiresu[6] = 120;		//コカコーラ
	siiresu[7] = 120;		//三ツ矢サイダー
	siiresu[8] = 120;		//なっちゃん
	siiresu[9] = 120;		//アクエリアス
	siiresu[10] = 330;		//かき氷（ブルーハワイ）
	siiresu[11] = 330;		//かき氷（いちご）
	siiresu[12] = 330;		//かき氷（パイン）
	siiresu[13] = 60;		//練乳オプション
	//siiresu[14] = 0;		//値引き


	//販売単価設定
	tanka[0] = 100;
	tanka[1] = 100;
	tanka[2] = 100;
	tanka[3] = 100;
	tanka[4] = 350;
	tanka[5] = 100;
	tanka[6] = 100;
	tanka[7] = 100;
	tanka[8] = 100;
	tanka[9] = 100;
	tanka[10] = 100;
	tanka[11] = 100;
	tanka[12] = 100;
	tanka[13] = 0;
	//tanka[14] = -30;


	//販売数初期化
	hambaisu[0] = 0;
	hambaisu[1] = 0;
	hambaisu[2] = 0;
	hambaisu[3] = 0;
	hambaisu[4] = 0;
	hambaisu[5] = 0;
	hambaisu[6] = 0;
	hambaisu[7] = 0;
	hambaisu[8] = 0;
	hambaisu[9] = 0;
	hambaisu[10] = 0;
	hambaisu[11] = 0;
	hambaisu[12] = 0;
	hambaisu[13] = 0;
	//hambaisu[14] = 0;

	prevhambaisu[0] = 0;
	prevhambaisu[1] = 0;
	prevhambaisu[2] = 0;
	prevhambaisu[3] = 0;
	prevhambaisu[4] = 0;
	prevhambaisu[5] = 0;
	prevhambaisu[6] = 0;
	prevhambaisu[7] = 0;
	prevhambaisu[8] = 0;
	prevhambaisu[9] = 0;
	prevhambaisu[10] = 0;
	prevhambaisu[11] = 0;
	prevhambaisu[12] = 0;
	prevhambaisu[13] = 0;
	//prevhambaisu[14] = 0;


	//各種データ初期化
	sougaku = 0;
	kyaku = 0;
	no = 0;


	//準備金入力
	jumbikin = 52500;


	//仕入れ総額(1日分)入力
	siire = 148075;


	printf("Version 5.3.3\n\n");
	printf("おはようございます！\n仕入れ数，販売単価，準備金，仕入れ総額を確認してください．\n\n\n");
	for (i = 0; i <= 13; i++){
		switch (i){
		case 0:
			strcpy_s(disp, "おにぎり（鮭）\t");
			break;
		case 1:
			strcpy_s(disp, "おにぎり（明太子）");
			break;
		case 2:
			strcpy_s(disp, "おにぎり（ツナマヨ）");
			break;
		case 3:
			strcpy_s(disp, "おにぎり（黒豚焼肉）");
			break;
		case 4:
			strcpy_s(disp, "冷やし中華\t");
			break;
		case 5:
			strcpy_s(disp, "ウーロン茶\t");
			break;
		case 6:
			strcpy_s(disp, "コカコーラ\t");
			break;
		case 7:
			strcpy_s(disp, "三ツ矢サイダー\t");
			break;
		case 8:
			strcpy_s(disp, "なっちゃん\t");
			break;
		case 9:
			strcpy_s(disp, "アクエリアス\t");
			break;
		case 10:
			strcpy_s(disp, "かき氷（ブルーハワイ）");
			break;
		case 11:
			strcpy_s(disp, "かき氷（いちご）");
			break;
		case 12:
			strcpy_s(disp, "かき氷（パイン）");
			break;
		case 13:
			strcpy_s(disp, "練乳オプション\t");
			break;
			//case 14:
			//strcpy_s(disp, "値引き\t\t");
			//break;
		}
		printf("%s\t:仕入れ数%d個，単価\\%d\n", disp, siiresu[i], tanka[i]);
	}
	printf("準備金\t\t\t:\\%d", jumbikin);
	printf("\n仕入れ総額\t\t:\\%d\n", siire);
	printf("\n\n上記の値に誤りはありませんか？\nある:0　ない:1　=>");
	gets_s(buffer);
	roop = atoi(buffer);
	confirm = 0;
	deletetype = 0;

	if (roop == 1){
		printf("\n開局します．");
		err3 = fopen_s(&log3, "siirehenkoulog.txt", "a");
		if (err3 == 0)
		{
			fprintf(log3, "\n\n%p\t営業開始時：\n", "a");
			for (i = 0; i <= 13; i++){
				fprintf(log3, "%p\t[%d]:%d個\n", "a", i, siiresu[i]);
			}
			fprintf(log3, "%p\t仕入れ総額\\%d\n", "a", siire);
		}
		else
		{
			printf("siirehenkoulog.txtが開けませんでした\n");
		}
		fclose(log3);
		printf("Enterキーを押してください．");
		command = getchar();
		rewind(stdin);
	}
	else {
		printf("\n戻って修正してください．\n\n");
	}

	while (roop == 1){

		if (confirm != 1){

			switch (command){

			case '\n':
				n = 0;
				for (i = 0; i <= 12; i++){
					n = n + (siiresu[i] - hambaisu[i]);
				}
				if (n == 0){
					printf("\n-----------------------------------------------------------------------------\n販売できる商品がありません．\n");
				}
				else{
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
					for (i = 0; i <= 13; i++){
						if (siiresu[i] - hambaisu[i] <= 5 && siiresu[i] - hambaisu[i] != 0){
							switch (i){
							case 0:
								strcpy_s(disp, "おにぎり（鮭）\t");
								break;
							case 1:
								strcpy_s(disp, "おにぎり（明太子）");
								break;
							case 2:
								strcpy_s(disp, "おにぎり（ツナマヨ）");
								break;
							case 3:
								strcpy_s(disp, "おにぎり（黒豚焼肉）");
								break;
							case 4:
								strcpy_s(disp, "冷やし中華\t");
								break;
							case 5:
								strcpy_s(disp, "ウーロン茶\t");
								break;
							case 6:
								strcpy_s(disp, "コカコーラ\t");
								break;
							case 7:
								strcpy_s(disp, "三ツ矢サイダー\t");
								break;
							case 8:
								strcpy_s(disp, "なっちゃん\t");
								break;
							case 9:
								strcpy_s(disp, "アクエリアス\t");
								break;
							case 10:
								strcpy_s(disp, "かき氷（ブルーハワイ）");
								break;
							case 11:
								strcpy_s(disp, "かき氷（いちご）");
								break;
							case 12:
								strcpy_s(disp, "かき氷（パイン）");
								break;
							case 13:
								strcpy_s(disp, "練乳オプション\t");
								break;
								//case 14:
								//strcpy_s(disp, "値引き\t\t");
								//break;
							}
							printf("【在庫僅少】\t%s\tは残り%d個です．\n", disp, siiresu[i] - hambaisu[i]);
						}
						else if (siiresu[i] - hambaisu[i] == 0){
							switch (i){
							case 0:
								strcpy_s(disp, "おにぎり（鮭）\t");
								break;
							case 1:
								strcpy_s(disp, "おにぎり（明太子）");
								break;
							case 2:
								strcpy_s(disp, "おにぎり（ツナマヨ）");
								break;
							case 3:
								strcpy_s(disp, "おにぎり（黒豚焼肉）");
								break;
							case 4:
								strcpy_s(disp, "冷やし中華\t");
								break;
							case 5:
								strcpy_s(disp, "ウーロン茶\t");
								break;
							case 6:
								strcpy_s(disp, "コカコーラ\t");
								break;
							case 7:
								strcpy_s(disp, "三ツ矢サイダー\t");
								break;
							case 8:
								strcpy_s(disp, "なっちゃん\t");
								break;
							case 9:
								strcpy_s(disp, "アクエリアス\t");
								break;
							case 10:
								strcpy_s(disp, "かき氷（ブルーハワイ）");
								break;
							case 11:
								strcpy_s(disp, "かき氷（いちご）");
								break;
							case 12:
								strcpy_s(disp, "かき氷（パイン）");
								break;
							case 13:
								strcpy_s(disp, "練乳オプション\t");
								break;
								//case 14:
								//strcpy_s(disp, "値引き\t\t");
								//break;
							}
							printf("【完　　売】\t%s\tは完売いたしました．\n", disp);
						}
					}

					printf("\n\n取引No.%d ------------------------------------------------------------------\nいらっしゃいませ! ご注文をどうぞ．\n\n\n", no + 1);
					code = 1;
					codeerror = 0;
					tensuu = 0;
					goukei = 0;
					kosu = 0;
					azukari = 0;

					while (code != 0) {

						printf("CODE:");
						gets_s(buffer);
						code = atoi(buffer);

						if (code < 1000){

							if (code == 0){}

							else {
								switch (code){
								case 11:
									i = 0;
									strcpy_s(disp, "おにぎり（鮭）\t");
									break;
								case 12:
									i = 1;
									strcpy_s(disp, "おにぎり（明太子）");
									break;
								case 13:
									i = 2;
									strcpy_s(disp, "おにぎり（ツナマヨ）");
									break;
								case 14:
									i = 3;
									strcpy_s(disp, "おにぎり（黒豚焼肉）");
									break;
								case 21:
									i = 4;
									strcpy_s(disp, "冷やし中華\t");
									break;
								case 31:
									i = 5;
									strcpy_s(disp, "ウーロン茶\t");
									break;
								case 32:
									i = 6;
									strcpy_s(disp, "コカコーラ\t");
									break;
								case 33:
									i = 7;
									strcpy_s(disp, "三ツ矢サイダー\t");
									break;
								case 34:
									i = 8;
									strcpy_s(disp, "なっちゃん\t");
									break;
								case 35:
									i = 9;
									strcpy_s(disp, "アクエリアス\t");
									break;
								case 41:
									i = 10;
									strcpy_s(disp, "かき氷（ブルーハワイ）");
									break;
								case 42:
									i = 11;
									strcpy_s(disp, "かき氷（いちご）");
									break;
								case 43:
									i = 12;
									strcpy_s(disp, "かき氷（パイン）");
									break;
								case 44:
									i = 13;
									strcpy_s(disp, "■練乳オプション");
									break;
									//case 99:
									//i = 14;
									//strcpy_s(disp, "■値引き\t");
									//break;
								default:
									printf("\t<<WRONG CODE>>\n\n");
									codeerror = 1;
									break;
								}

								if (codeerror == 1){
									codeerror = 0;
								}
								else{
									printf(disp);
									printf("\tQTY:");
									gets_s(buffer);
									kosu = atoi(buffer);
									while (kosu < 0 || kosu > siiresu[i] - hambaisu[i]){
										if (kosu < 0)
										{
											printf("\t<<WRONG QUANTITY>>\n");
											printf("\t\t\tQTY:");
											gets_s(buffer);
											kosu = atoi(buffer);
										}
										else if (kosu > siiresu[i] - hambaisu[i])
										{
											printf("\t恐れ入ります．現在の在庫は%d個です．\n", siiresu[i] - hambaisu[i]);
											printf("\t\t\tQTY:");
											gets_s(buffer);
											kosu = atoi(buffer);
										}
									}
									printf("\t単価\\%d × %d個　　小計:\\%d\n\n", tanka[i], kosu, tanka[i] * kosu);
									goukei = goukei + tanka[i] * kosu;
									if (i == 13 || i == 14){}
									else{
										tensuu = tensuu + kosu;
									}
									hambaisu[i] = hambaisu[i] + kosu;
								}
							}
						}
						else if (code >= 1000){

							switch (code){

							case 1011:
								i = 0;
								strcpy_s(disp, "【取消】おにぎり（鮭）\t");
								break;
							case 1012:
								i = 1;
								strcpy_s(disp, "【取消】おにぎり（明太子）");
								break;
							case 1013:
								i = 2;
								strcpy_s(disp, "【取消】おにぎり（ツナマヨ）");
								break;
							case 1014:
								i = 3;
								strcpy_s(disp, "【取消】おにぎり（黒豚焼肉）");
								break;
							case 1021:
								i = 4;
								strcpy_s(disp, "【取消】冷やし中華\t");
								break;
							case 1031:
								i = 5;
								strcpy_s(disp, "【取消】ウーロン茶\t");
								break;
							case 1032:
								i = 6;
								strcpy_s(disp, "【取消】コカコーラ\t");
								break;
							case 1033:
								i = 7;
								strcpy_s(disp, "【取消】三ツ矢サイダー\t");
								break;
							case 1034:
								i = 8;
								strcpy_s(disp, "【取消】なっちゃん\t");
								break;
							case 1035:
								i = 9;
								strcpy_s(disp, "【取消】アクエリアス\t");
								break;
							case 1041:
								i = 10;
								strcpy_s(disp, "【取消】かき氷（ブルーハワイ）");
								break;
							case 1042:
								i = 11;
								strcpy_s(disp, "【取消】かき氷（いちご）");
								break;
							case 1043:
								i = 12;
								strcpy_s(disp, "【取消】かき氷（パイン）");
								break;
							case 1044:
								i = 13;
								strcpy_s(disp, "【取消】■練乳オプション");
								break;
								//case 1099:
								//i = 14;
								//strcpy_s(disp, "【取消】■値引き\t");
								//break;
							default:
								printf("\t<<WRONG CODE>>\n\n");
								codeerror = 1;
								break;
							}

							if (codeerror == 1){
								codeerror = 0;
							}
							else{
								printf(disp);
								printf("\tQTY:");
								gets_s(buffer);
								kosu = atoi(buffer);
								while (kosu < 0 || kosu > hambaisu[i] - prevhambaisu[i]){
									if (kosu < 0)
									{
										printf("\t<<WRONG QUANTITY>>\n");
										printf("\t\t\tQTY:");
										gets_s(buffer);
										kosu = atoi(buffer);
									}
									else if (kosu > hambaisu[i] - prevhambaisu[i])
									{
										printf("\t恐れ入ります．この取引でのオーダー数は%d個です．\n", hambaisu[i] - prevhambaisu[i]);
										printf("\t\t\tQTY:");
										gets_s(buffer);
										kosu = atoi(buffer);
									}
								}
								printf("\t単価\\%d × %d個　　小計:\\%d\n\n", tanka[i], -kosu, -tanka[i] * kosu);
								goukei = goukei - tanka[i] * kosu;
								if (i == 13 || i == 14){}
								else{
									tensuu = tensuu - kosu;
								}
								hambaisu[i] = hambaisu[i] - kosu;
							}
						}
					}

					printf("\n\tお買上点数:%d  《 合計 : \\%d 》\n\n", tensuu, goukei);
					sougaku = sougaku + goukei;
					printf("TENDERED:");
					gets_s(buffer);
					azukari = atoi(buffer);
					while (azukari < goukei)
					{
						printf("\t<<WRONG TENDERED CASH>>\n");
						printf("TENDERED:");
						gets_s(buffer);
						azukari = atoi(buffer);
					}
					printf("\t《 お預り : \\%d 》\n", azukari);
					printf("\t《 お釣り : \\%d 》\n\n", azukari - goukei);
					printf("お買い上げありがとうございました!\n\n");
					if (goukei > 0){

						kyaku++;
						no++;

						err2 = fopen_s(&log2, "urilog.txt", "a");
						if (err2 == 0)
						{
							fprintf(log2, "\n\n%p\t取引No.%d終了後：\n", "a", no);
							fprintf(log2, "%p\t売上高\\%d，客数%d人\n", "a", sougaku, kyaku);
							for (i = 0; i <= 13; i++){
								fprintf(log2, "%p\t[%d]:%d個\n", "a", i, hambaisu[i]);
							}
						}
						else
						{
							printf("urilog.txtが開けませんでした\n");
						}
						fclose(log2);

					}
					else {}

					for (i = 0; i <= 13; i++){
						prevhambaisu[i] = hambaisu[i];
					}
				}

				//printf("COMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'n':
				printf("\n\n-----------------------------------------------------------------------------\n現在の在庫を表示します．\n\n");
				for (i = 0; i <= 13; i++){
					switch (i){
					case 0:
						strcpy_s(disp, "おにぎり（鮭）\t");
						break;
					case 1:
						strcpy_s(disp, "おにぎり（明太子）");
						break;
					case 2:
						strcpy_s(disp, "おにぎり（ツナマヨ）");
						break;
					case 3:
						strcpy_s(disp, "おにぎり（黒豚焼肉）");
						break;
					case 4:
						strcpy_s(disp, "冷やし中華\t");
						break;
					case 5:
						strcpy_s(disp, "ウーロン茶\t");
						break;
					case 6:
						strcpy_s(disp, "コカコーラ\t");
						break;
					case 7:
						strcpy_s(disp, "三ツ矢サイダー\t");
						break;
					case 8:
						strcpy_s(disp, "なっちゃん\t");
						break;
					case 9:
						strcpy_s(disp, "アクエリアス\t");
						break;
					case 10:
						strcpy_s(disp, "かき氷（ブルーハワイ）");
						break;
					case 11:
						strcpy_s(disp, "かき氷（いちご）");
						break;
					case 12:
						strcpy_s(disp, "かき氷（パイン）");
						break;
					case 13:
						strcpy_s(disp, "練乳オプション\t");
						break;
						//case 14:
						//strcpy_s(disp, "値引き\t\t");
						//break;
					}
					printf("%s\t:%d個\n", disp, siiresu[i] - hambaisu[i]);
				}

				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'h':
				printf("\n\n-----------------------------------------------------------------------------\n現在の販売数を表示します．\n\n");
				for (i = 0; i <= 13; i++){
					switch (i){
					case 0:
						strcpy_s(disp, "おにぎり（鮭）\t");
						break;
					case 1:
						strcpy_s(disp, "おにぎり（明太子）");
						break;
					case 2:
						strcpy_s(disp, "おにぎり（ツナマヨ）");
						break;
					case 3:
						strcpy_s(disp, "おにぎり（黒豚焼肉）");
						break;
					case 4:
						strcpy_s(disp, "冷やし中華\t");
						break;
					case 5:
						strcpy_s(disp, "ウーロン茶\t");
						break;
					case 6:
						strcpy_s(disp, "コカコーラ\t");
						break;
					case 7:
						strcpy_s(disp, "三ツ矢サイダー\t");
						break;
					case 8:
						strcpy_s(disp, "なっちゃん\t");
						break;
					case 9:
						strcpy_s(disp, "アクエリアス\t");
						break;
					case 10:
						strcpy_s(disp, "かき氷（ブルーハワイ）");
						break;
					case 11:
						strcpy_s(disp, "かき氷（いちご）");
						break;
					case 12:
						strcpy_s(disp, "かき氷（パイン）");
						break;
					case 13:
						strcpy_s(disp, "練乳オプション\t");
						break;
						//case 14:
						//strcpy_s(disp, "値引き\t\t");
						//break;
					}
					printf("%s\t:%d個\t販売額:\\%d\n", disp, hambaisu[i], tanka[i] * hambaisu[i]);
				}

				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'p':
				printf("\n\n-----------------------------------------------------------------------------\n商品の単価を表示します．\n\n");
				for (i = 0; i <= 13; i++){
					switch (i){
					case 0:
						strcpy_s(disp, "おにぎり（鮭）\t");
						break;
					case 1:
						strcpy_s(disp, "おにぎり（明太子）");
						break;
					case 2:
						strcpy_s(disp, "おにぎり（ツナマヨ）");
						break;
					case 3:
						strcpy_s(disp, "おにぎり（黒豚焼肉）");
						break;
					case 4:
						strcpy_s(disp, "冷やし中華\t");
						break;
					case 5:
						strcpy_s(disp, "ウーロン茶\t");
						break;
					case 6:
						strcpy_s(disp, "コカコーラ\t");
						break;
					case 7:
						strcpy_s(disp, "三ツ矢サイダー\t");
						break;
					case 8:
						strcpy_s(disp, "なっちゃん\t");
						break;
					case 9:
						strcpy_s(disp, "アクエリアス\t");
						break;
					case 10:
						strcpy_s(disp, "かき氷（ブルーハワイ）");
						break;
					case 11:
						strcpy_s(disp, "かき氷（いちご）");
						break;
					case 12:
						strcpy_s(disp, "かき氷（パイン）");
						break;
					case 13:
						strcpy_s(disp, "練乳オプション\t");
						break;
						//case 14:
						//strcpy_s(disp, "値引き\t\t");
						//break;
					}
					printf("%s\t:\\%d\n", disp, tanka[i]);
				}

				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'c':
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t申し訳ございません\n\t\tただいま休止中です...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

				//printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'k':
				printf("\n\n-----------------------------------------------------------------------------\n現在の客数を表示します．\n\n");
				printf("客数\t:%d人\n",kyaku);

				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'v':
				printf("\n\n-----------------------------------------------------------------------------\nバージョン情報\n\n");
				printf("Cash Register Software\nVersion 5.3.3\n2017.9.7 Programmed by Atsushi Kambayashi\n");

				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'd':
				printf("\n\n-----------------------------------------------------------------------------\n販売取り消し処理を行います．\n\n");
				code = 1;
				codeerror = 0;
				tensuu = 0;
				goukei = 0;
				kosu = 0;
				//azukari = 0;
				printf("取り消し操作の種別を選択してください．\n　商品単位で取り消す:0　取引単位で取り消す(全取消):1　=>");
				gets_s(buffer);
				deletetype = atoi(buffer);
				printf("\n");
				while (code != 0) {
					printf("取り消す商品のCODE:");
					gets_s(buffer);
					code = atoi(buffer);
					if (code == 0){}
					else {
						switch (code){
						case 11:
							i = 0;
							strcpy_s(disp, "【取消】おにぎり（鮭）\t");
							break;
						case 12:
							i = 1;
							strcpy_s(disp, "【取消】おにぎり（明太子）");
							break;
						case 13:
							i = 2;
							strcpy_s(disp, "【取消】おにぎり（ツナマヨ）");
							break;
						case 14:
							i = 3;
							strcpy_s(disp, "【取消】おにぎり（黒豚焼肉）");
							break;
						case 21:
							i = 4;
							strcpy_s(disp, "【取消】冷やし中華\t");
							break;
						case 31:
							i = 5;
							strcpy_s(disp, "【取消】ウーロン茶\t");
							break;
						case 32:
							i = 6;
							strcpy_s(disp, "【取消】コカコーラ\t");
							break;
						case 33:
							i = 7;
							strcpy_s(disp, "【取消】三ツ矢サイダー\t");
							break;
						case 34:
							i = 8;
							strcpy_s(disp, "【取消】なっちゃん\t");
							break;
						case 35:
							i = 9;
							strcpy_s(disp, "【取消】アクエリアス\t");
							break;
						case 41:
							i = 10;
							strcpy_s(disp, "【取消】かき氷（ブルーハワイ）");
							break;
						case 42:
							i = 11;
							strcpy_s(disp, "【取消】かき氷（いちご）");
							break;
						case 43:
							i = 12;
							strcpy_s(disp, "【取消】かき氷（パイン）");
							break;
						case 44:
							i = 13;
							strcpy_s(disp, "【取消】■練乳オプション");
							break;
							//case 99:
							//i = 14;
							//strcpy_s(disp, "【取消】■値引き\t");
							//break;
						default:
							printf("\t<<WRONG CODE>>\n\n");
							codeerror = 1;
							break;
						}
						if (codeerror == 1){
							codeerror = 0;
						}
						else{
							printf(disp);
							printf("\tQTY:");
							gets_s(buffer);
							kosu = atoi(buffer);
							while (kosu < 0 || kosu > hambaisu[i]){
								if (kosu < 0)
								{
									printf("\t<<WRONG QUANTITY>>\n");
									printf("\t\t\t\tQTY:");
									gets_s(buffer);
									kosu = atoi(buffer);
								}
								else if (kosu > hambaisu[i]){
									printf("\t恐れ入ります．現在の販売数は%d個です．\n", hambaisu[i]);
									printf("\t\t\t\tQTY:");
									gets_s(buffer);
									kosu = atoi(buffer);
								}
							}
							printf("\t単価\\%d × %d個　　小計:\\%d\n\n", tanka[i], kosu, tanka[i] * kosu);
							goukei = goukei + tanka[i] * kosu;
							tensuu = tensuu + kosu;
							hambaisu[i] = hambaisu[i] - kosu;
						}
					}
				}

				printf("\n\t取り消し件数:%d  《 返金合計 : \\%d 》\n\n", tensuu, goukei);
				sougaku = sougaku - goukei;
				printf("ありがとうございました．\n\n");
				if (goukei > 0){

					if (deletetype == 1){
						kyaku--;
					}

					err2 = fopen_s(&log2, "urilog.txt", "a");
					if (err2 == 0)
					{
						fprintf(log2, "\n\n%p\t取消操作終了後：\n", "a");
						fprintf(log2, "%p\t売上高\\%d，客数%d人\n", "a", sougaku, kyaku);
						for (i = 0; i <= 13; i++){
							fprintf(log2, "%p\t[%d]:%d個\n", "a", i, hambaisu[i]);
						}
					}
					else
					{
						printf("urilog.txtが開けませんでした\n");
					}
					fclose(log2);

				}
				else {}

				for (i = 0; i <= 13; i++){
					prevhambaisu[i] = hambaisu[i];
				}

				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 't':
				printf("\n\n-----------------------------------------------------------------------------\n点検処理を行います．現在の実在高を入力してください．:\\");
				gets_s(buffer);
				aridaka = atoi(buffer);
				printf("\n\n　　　客数:%d人\n", kyaku);
				printf("\n　　準備金:\\%d\n", jumbikin);
				printf("　　売上高:\\%d\n", sougaku);
				printf("　計算在高:\\%d\n", jumbikin + sougaku);
				printf("　　実在高:\\%d\n", aridaka);
				printf("現金過不足:\\%d\n", aridaka - jumbikin - sougaku);
				printf("\n売上総利益:\\%d", sougaku - siire);
				if (sougaku - siire >= 0){
					printf("\t【黒字】\n");
				}
				else {
					printf("\t【赤字】\n");
				}

				err = fopen_s(&log, "akaneyalog.txt", "a");
				if (err == 0)
				{
					fprintf(log, "\n\n%p【点検】客数%d人，売上高\\%d，計算在高\\%d，過不足\\%d，利益\\%d\n", "a", kyaku, sougaku, jumbikin + sougaku, aridaka - jumbikin - sougaku, sougaku - siire);
					for (i = 0; i <= 13; i++){
						fprintf(log, "%p\t[%d]:%d個\n", "a", i, hambaisu[i]);
					}
					printf("\n\nakaneyalog.txtにログを出力しました．\n");
				}
				else
				{
					printf("\n\nakaneyalog.txtが開けませんでした．\n");
				}
				fclose(log);

				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'l':
				printf("\n\n-----------------------------------------------------------------------------\nakaneyalog.txtにログを出力します．\n\n");
				err = fopen_s(&log, "akaneyalog.txt", "a");
				if (err == 0)
				{
					printf("akaneyalog.txtは正常にオープンされました．\n");
					fprintf(log, "\n\n%p\t客数%d人，売上高\\%d，計算在高\\%d\n", "a", kyaku, sougaku, jumbikin + sougaku);
					for (i = 0; i <= 13; i++){
						fprintf(log, "%p\t[%d]:%d個\n", "a", i, hambaisu[i]);
					}
				}
				else
				{
					printf("akaneyalog.txtが開けませんでした．\n");
				}
				fclose(log);
				printf("akaneyalog.txtは正常にクローズされました．\n");

				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'e':
				printf("\n\n-----------------------------------------------------------------------------\nakaneyalog.txt，urilog.txt，siirehenkoulog.txtのログを削除します．\n\n");
				printf("本当に削除してよろしいですか?\n中止:0　削除:1　=>");
				gets_s(buffer);
				confirm = atoi(buffer);

				if (confirm == 1){
					err = fopen_s(&log, "akaneyalog.txt", "w");
					if (err == 0)
					{
						fprintf(log, "", "w");
						printf("\nakaneyalog.txtをクリアしました．\n");
					}
					else
					{
						printf("\nakaneyalog.txtが開けませんでした．\n");
					}
					fclose(log);
					err2 = fopen_s(&log2, "urilog.txt", "w");
					if (err2 == 0)
					{
						fprintf(log2, "", "w");
						printf("urilog.txtをクリアしました．\n");
					}
					else
					{
						printf("urilog.txtが開けませんでした．\n");
					}
					fclose(log2);
					err3 = fopen_s(&log3, "siirehenkoulog.txt", "w");
					if (err3 == 0)
					{
						fprintf(log3, "", "w");
						printf("siirehenkoulog.txtをクリアしました．\n");
					}
					else
					{
						printf("siirehenkoulog.txtが開けませんでした．\n");
					}
					fclose(log3);
					confirm = 0;
				}
				else{
					printf("\n削除を中止しました．\n");
					confirm = 0;
				}
				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case 'a':
				karisiire = 0;
				printf("\n\n-----------------------------------------------------------------------------\n仕入れ数を変更します．配列番号を指定してください．\n\n");
				printf("配列番号:");
				gets_s(buffer);
				i = atoi(buffer);
				if (i >= 0 && i <= 13){
					printf("\n現在の[%d]の仕入れ数は%d個です.\n新しい仕入れ数を入力してください．:", i, siiresu[i]);
					gets_s(buffer);
					karisiire = atoi(buffer);
					if (karisiire >= hambaisu[i]){
						siiresu[i] = karisiire;
						printf("\n[%d]の仕入れ数は%d個に変更されました．現在の[%d]の在庫数は%d個です．", i, siiresu[i], i, siiresu[i] - hambaisu[i]);
						printf("\n\n現在の仕入れ総額(1日分)は%d円です．\n新しい仕入れ総額を入力してください．\nただし商品ロスなどの場合は変更しないでください．:", siire);
						gets_s(buffer);
						siire = atoi(buffer);
						printf("\n仕入れ総額は%d円に変更されました．\n\n", siire);

						err3 = fopen_s(&log3, "siirehenkoulog.txt", "a");
						if (err3 == 0)
						{
							fprintf(log3, "\n\n%p\t仕入れ数変更操作後：\n", "a");
							for (i = 0; i <= 13; i++){
								fprintf(log3, "%p\t[%d]:%d個\n", "a", i, siiresu[i]);
							}
							fprintf(log3, "%p\t仕入れ総額\\%d\n", "a", siire);
						}
						else
						{
							printf("siirehenkoulog.txtが開けませんでした\n");
						}
						fclose(log3);
					}
					else {
						printf("\n仕入れ数を販売数より小さく変更することはできません．\n\n");
					}
				}
				else {
					printf("\n存在しない配列番号が指定されました．\n\n");
				}
				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;

			case EOF:
				printf("\n\n-----------------------------------------------------------------------------\n本当に販売処理を終了しますか?\n\"終了する\"を選択すると他の操作には戻れなくなります．\n\n");
				printf("販売処理を継続する:0  終了する:1  =>");

				gets_s(buffer);
				confirm = atoi(buffer);
				command = '\n';
				break;
							
			/*
			case 'x':
				printf("\n");
				roop = 0;
				break;
			*/

			default:
				printf("<<COMMAND NOT FOUND>>");
				printf("\nCOMMAND:");
				command = getchar();
				rewind(stdin);
				break;
			}
		}

		else {
			confirm = 0;
			printf("\n\n-----------------------------------------------------------------------------\n精算処理を行います．現在の実在高を入力してください．:\\");
			gets_s(buffer);
			aridaka = atoi(buffer);
			while (confirm != 1){
				printf("\n実在高を\\%dで確定します．よろしいですか？\n修正する:0　確定する:1　=>", aridaka);
				gets_s(buffer);
				confirm = atoi(buffer);
				if (confirm != 1){
					printf("\n現在の実在高を入力してください．:\\");
					gets_s(buffer);
					aridaka = atoi(buffer);
				}
			}
			printf("\n\n************************売上データ************************");
			printf("\n\n　　　　客数:%d人\n", kyaku);
			printf("　　　準備金:\\%d\n\n", jumbikin);
			printf("　　　売上高:\\%d\n\t内訳:\n", sougaku);
			for (i = 0; i <= 13; i++){
				switch (i){
				case 0:
					strcpy_s(disp, "おにぎり（鮭）\t");
					break;
				case 1:
					strcpy_s(disp, "おにぎり（明太子）");
					break;
				case 2:
					strcpy_s(disp, "おにぎり（ツナマヨ）");
					break;
				case 3:
					strcpy_s(disp, "おにぎり（黒豚焼肉）");
					break;
				case 4:
					strcpy_s(disp, "冷やし中華\t");
					break;
				case 5:
					strcpy_s(disp, "ウーロン茶\t");
					break;
				case 6:
					strcpy_s(disp, "コカコーラ\t");
					break;
				case 7:
					strcpy_s(disp, "三ツ矢サイダー\t");
					break;
				case 8:
					strcpy_s(disp, "なっちゃん\t");
					break;
				case 9:
					strcpy_s(disp, "アクエリアス\t");
					break;
				case 10:
					strcpy_s(disp, "かき氷（ブルーハワイ）");
					break;
				case 11:
					strcpy_s(disp, "かき氷（いちご）");
					break;
				case 12:
					strcpy_s(disp, "かき氷（パイン）");
					break;
				case 13:
					strcpy_s(disp, "練乳オプション\t");
					break;
					//case 14:
					//strcpy_s(disp, "値引き\t\t");
					//break;
				}
				printf("\t%s\t:\\%d×%d個 = \\%d\n", disp, tanka[i], hambaisu[i], tanka[i] * hambaisu[i]);
			}
			printf("\n　　計算在高:\\%d\n", jumbikin + sougaku);
			printf("　　　実在高:\\%d\n", aridaka);
			printf("　現金過不足:\\%d\n", aridaka - jumbikin - sougaku);
			printf("\n　売上総利益:\\%d", sougaku - siire);
			if (sougaku - siire >= 0){
				printf("\t【黒字】\n");
			}
			else {
				printf("\t【赤字】\n");
			}
			printf("\n**********************************************************\n");
			printf("閉局します．Enterキーを押してください．");
			gets_s(buffer);
			printf("\n");

			err = fopen_s(&log, "akaneyalog.txt", "a");
			if (err == 0)
			{
				fprintf(log, "\n\n%p【精算】客数%d人，売上高\\%d，計算在高\\%d，過不足\\%d，利益\\%d\n", "a", kyaku, sougaku, jumbikin + sougaku, aridaka - jumbikin - sougaku, sougaku - siire);
				for (i = 0; i <= 13; i++){
					fprintf(log, "%p\t[%d]:%d個\n", "a", i, hambaisu[i]);
				}
				printf("\nakaneyalog.txtにログを出力しました．\n");
			}
			else
			{
				printf("\n\nakaneyalog.txtが開けませんでした．\n");
			}
			fclose(log);

			printf("\nお疲れさまでした!!!\n\n-----------------------------------------------------------------------------\n\n");
			roop = 0;
		}
	}


	return 0;

}


//Cash Register Software for Akaneya
//Version 5.3.3
//2017.9.7 Written by @Toramin10
