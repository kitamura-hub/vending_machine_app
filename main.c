#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(void) {
  int total_sales = 0;  // 総売上
  // 総釣銭の初期化
  total_change t_chnage_data = { 0, 0, 0, 0, 0 };
  // 商品データの代入(初期化)
  product product_data[6] = {
    { 1, "水      ", 120, 3 }, { 2, "お茶    ", 130, 5 }, { 3, "紅茶    ", 110, 7 },
    { 4, "オレンジ", 100, 9 }, { 5, "コーラ  ", 110, 3 }, { 6, "ファンタ", 140, 5 }
  };

  // for (int i=0; i<6; i++) {
  //   printf("【%d】%s: %d円 | 残り: %d\n", product_data[i].product_id, product_data[i].product_name, product_data[i].price, product_data[i].stock);
  // }

  return 0;
}