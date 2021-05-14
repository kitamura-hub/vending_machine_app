#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 羅列されてる数値以外の数値をtureにするための条件式
#define BETWEEN_0_TO_4 mode_num != 0 && mode_num != 1 && mode_num != 2 && mode_num != 3 && mode_num != 4  // モード番号
#define BETWEEN_1_TO_6 inp != 1 && inp != 2 && inp != 3 && inp != 4 && inp != 5 && inp != 6  // 商品番号
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
void payment(int *input);
void purchase_product(int *input_num, product *p_data);

int main(void) {
  int total_sales = 0;  // 総売上
  int mode_number = 0;  // モードハンドリングの数値
  int input_money = 0;  // 入金金額
  int input_p_num = 0;  // 入力商品番号
  total_change t_change_data = { 3, 5, 7, 9, 3 };  // 総釣銭
  product product_data[P_SIZE] = {  // 商品データの代入(初期化)
    { 1, "水      ", 120, 0 }, { 2, "お茶    ", 130, 3 }, { 3, "紅茶    ", 110, 5 },
    { 4, "オレンジ", 100, 7 }, { 5, "コーラ  ", 110, 9 }, { 6, "ファンタ", 140, 3 }
  };

  // 商品の一覧表示
  show_product(product_data);

  // モード選択
  mode_number = mode();
  if (mode_number == 1) {
    puts("購入者モード");
    payment(&input_money);  // 入金処理
    purchase_product(&input_p_num, product_data);  // 購入処理

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

void purchase_product(int *input_num, product *p_data) {
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
          printf("\n");
          break;  // 商品の購入成功でループから抜ける
        }
      }
    }

  } while(BETWEEN_1_TO_6 || p_data[i].stock <= 0);
  p_data[i].stock--;  // ユーザーの購入に従い、在庫数をデクリメントする
  *input_num = inp;  // input_p_numの値を更新
}