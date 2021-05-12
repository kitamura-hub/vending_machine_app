#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 0~4以外の数値はfalseにするための条件式
#define BETWEEN_0_TO_4 mode_num != 0 && mode_num != 1 && mode_num != 2 && mode_num != 3 && mode_num != 4
#define P_SIZE 6  // 商品データの要素数

// 総釣銭(釣銭で返却できる釣銭データ。各種枚数で管理)
typedef struct {
  int yen1000;
  int yen500;
  int yen100;
  int yen50;
  int yen10;
} total_change;

// 商品データ
typedef struct {
  const int product_id;
  const char product_name[64];
  const int price;
  int stock;
} product;

// プロトタイプ宣言
int mode(void);
void show_product(product p_data[P_SIZE]);

int main(void) {
  int total_sales = 0;  // 総売上
  int mode_number = 0;  // モードハンドリングの数値
  // 総釣銭の初期化
  total_change t_chnage_data = { 0, 0, 0, 0, 0 };
  // 商品データの代入(初期化)
  product product_data[P_SIZE] = {
    { 1, "水      ", 120, 3 }, { 2, "お茶    ", 130, 5 }, { 3, "紅茶    ", 110, 7 },
    { 4, "オレンジ", 100, 9 }, { 5, "コーラ  ", 110, 3 }, { 6, "ファンタ", 140, 5 }
  };


  // 商品の一覧表示
  show_product(product_data);

  // モード選択
  mode_number = mode();
  if (mode_number == 1) {
    puts("購入者モード");
  } else if (mode_number == 2) {
    puts("補充者モード");
  } else if (mode_number == 3) {
    puts("売上確認モード");
  } else if (mode_number == 4) {
    puts("釣銭確認モード");
  } else if (mode_number == 0) {
    puts("システムを終了します");
    exit(1);
  }

  return 0;
}

void show_product(product p_data[P_SIZE]) {
  for (int i=0; i<6; i++) {
    printf("【%d】%s: %d円 | 残り: %d\n", p_data[i].product_id, p_data[i].product_name, p_data[i].price, p_data[i].stock);
  }
  printf("\n");
}

int mode() {
  int mode_num = 0;
  puts("[1]:購入者モード \n[2]:補充者モード \n[3]:売上確認モード \n[4]:釣銭確認モード \n[0]:システムを終了する");
  do {
    printf("モードを選択してください: ");
    scanf("%d", &mode_num);
    if (BETWEEN_0_TO_4) puts("有効な数値を入力してください！！");
  } while(BETWEEN_0_TO_4);

  return mode_num;
}