#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 羅列されてる数値以外の数値をtureにするための条件式
#define BETWEEN_0_TO_4 mode_num != 0 && mode_num != 1 && mode_num != 2 && mode_num != 3 && mode_num != 4  // モード番号
#define BETWEEN_1_TO_6 inp != 1 && inp != 2 && inp != 3 && inp != 4 && inp != 5 && inp != 6  // 商品番号
#define P_SIZE 6  // 商品データの要素数

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
void payment(int *input);
void purchase_product(int *input_num, int *input_money, int *change, product *p_data);
void settle(int *total_sales, int *input_money, int *change, int *t_change);

int main(void) {
  int total_sales = 0;  // 総売上
  int mode_number = 0;  // モードハンドリングの数値
  int input_money = 0;  // 入金金額
  int input_p_num = 0;  // 入力商品番号
  int change = 0;  // 釣銭(整数値)
  int total_change[] = { 10, 11, 12, 13, 14 };  // 総釣銭 - 0: 1000円, 1: 500円, 2: 100円, 3: 50円, 4: 10円
  product product_data[P_SIZE] = {  // 商品データの代入(初期化)
    { 1, "水      ", 120, 0 }, { 2, "お茶    ", 130, 3 }, { 3, "紅茶    ", 110, 5 },
    { 4, "オレンジ", 100, 7 }, { 5, "コーラ  ", 110, 9 }, { 6, "ファンタ", 140, 3 }
  };

  show_product(product_data);  // 商品の一覧表示

  // モード選択
  mode_number = mode();
  if (mode_number == 1) {
    puts("購入者モード");
    payment(&input_money);  // 入金処理
    purchase_product(&input_p_num, &input_money, &change, product_data);  // 購入処理
    settle(&total_sales, &input_money, &change, total_change);  // 精算処理
  } else if (mode_number == 2) {
    puts("補充者モード");
  } else if (mode_number == 3) {
    puts("売上確認モード");
    printf("総売上: %d\n", total_sales);
  } else if (mode_number == 4) {
    puts("釣銭確認モード");
    // printf("1000円札: %d枚\n", total_change[0]);
    // printf("500円玉 : %d枚\n", total_change[1]);
    // printf("100円玉 : %d枚\n", total_change[2]);
    // printf("50円玉  : %d枚\n", total_change[3]);
    // printf("10円玉  : %d枚\n", total_change[4]);
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
  printf("\n");
  return mode_num;
}

void payment(int *input) {
  int inp = 0;  // ユーザーの入力を受け取る変数
  int y_n;  // y or n
  puts("投入金額の上限は1990円まで");

  do {
    printf("投入金額を入力: ");
    scanf("%d", &inp);
    printf("投入金額は%d円です。こちらの金額で本当によろしいですか？(1=yes or 0=no): ", inp);
    scanf("%d", &y_n);
    if (inp > 1990 && y_n == 1) puts("投入金額の上限(1990円)を超えています");
  } while(y_n == 0 || inp > 1990);
  printf("\n");
  *input = inp;  // input_moneyの値を更新
}

void purchase_product(int *input_num, int *input_money, int *change, product *p_data) {
  int inp = 0;  // ユーザーの入力を受け取る変数
  int i;
  do {
    printf("商品番号を入力してください(1 ~ 6): ");
    scanf("%d", &inp);
    if (BETWEEN_1_TO_6) puts("有効な商品番号を入力してください！！");

    for (i=0; i<P_SIZE; i++) {
      if (p_data[i].product_id == inp) {  // 選択した商品番号と商品データの商品番号をマッチ
        // 在庫判定
        if (p_data[i].stock <= 0) {
          printf("%sは現在、在庫がありません。商品を選び直してください\n", p_data[i].product_name);
        } else {
          printf("%sを購入しました！\n", p_data[i].product_name);
          break;  // 商品の購入成功でループから抜ける
        }
      }
    }

  } while(BETWEEN_1_TO_6 || p_data[i].stock <= 0);

  // 釣銭の返却(釣銭 = 入金金額 - 商品金額;)
  *change = *input_money - p_data[i].price;
  printf("お釣り: %d円\n", *change);
  printf("\n");

  p_data[i].stock--;  // ユーザーの購入に従い、在庫数をデクリメントする
  *input_num = inp;  // input_p_numの値を更新
}

void settle(int *total_sales, int *input_money, int *change, int *t_change) {
  int b1k = 0; int c500 = 0; int c100 = 0; int c50 = 0; int c10 = 0;

  // 総売上の更新
  *total_sales += *input_money - *change;

  // 紙幣と硬貨の枚数算出
  b1k = *change / 1000;
  *change = *change % 1000;
  c500 = *change / 500;
  *change = *change % 500;
  c100 = *change / 100;
  *change = *change % 100;
  c50 = *change / 50;
  *change = *change % 50;
  c10 = *change / 10;

  // 総釣銭の更新
  t_change[0] -= b1k;  // 1000円
  t_change[1] -= c500;  // 500円
  t_change[2] -= c100;  // 100円
  t_change[3] -= c50;  // 50円
  t_change[4] -= c10;  // 10円
}