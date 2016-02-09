#include <stdio.h>

/*
C言語学習用課題
コマンドラインを利用し、文字列oから指定文字列fを検索する
該当するものがあれば 検索文字列”xxx”が見つかりました
該当するものがなければ 検索文字列”xxx”が見つかりませんでした

コマンドライン
-o string: 検索対象テキスト
-f string: 検索文字列

エラーメッセージ
・引数が不正な場合
・その他

*/
int argchk(char* arg);				//コマンドライン引数の識別
void errmsg(int p);					//エラーメッセージ表示
int srch(char* org, char* match);	//検索

int Strlength(const char* s);		//文字列の長さを調べる


int main(int argc, char *argv[]){
	
	int chk;						//エラー検出用変数 0でなければエラー
	int s_org = 0;					//検索対象テキスト指定のオプション
	int s_find = 0;					//検索文字列指定のオプション
	
	for(int i = 1; i < argc; i++){	//1つ目のパラメータは実行ファイルなので弾く
//	ループ毎に1つずつコマンドラインオプションを取得する：argchk(argv[i])
		if (argchk(argv[i]) == 15){			//すでに検出されたものでないかチェック
			if (s_org == 0){
				s_org = i;					//-oがあった配列番号
			}else{
				chk = 1;
			}
		}
		if (argchk(argv[i]) == 6){
			if (s_find == 0){
				s_find = i;					//-fがあった配列番号
			}else{
				chk = 1;
			}
		}
	}
	
//	printf("s_org:%d\ns_find:%d\n", s_org, s_find);
	if (chk == 0) {
		chk = srch(argv[s_org+1], argv[s_find+1]);		//検索
	}
	errmsg(chk);					//エラーメッセージを表示
	return 0;
}


//コマンドライン引数の識別
int argchk(char* arg){
	if (arg[0] == '-'){
		if (arg[1] == 'f'){
			return 6;
		} else if (arg[1] == 'o'){
			return 15;
		}
	}else{
		return 0;
	}
	return 0;
}


//検索
int srch(char* org, char* match){
	//	方針:1文字目を探す→全一致かどうか確認する
	int orglength = Strlength(org);
	int matchlength = Strlength(match);
	int scm = orglength - matchlength + 1; //サーチ回数
	int srchresult = 0;				//発見回数
	
//	printf("%s:%d\n", org, orglength);
//	printf("%s:%d\n", match, matchlength);
	
	if (scm <= 0) {
		return 2;					//検索文字列が対象文字列より長い
	}
	
	int i;	int j;
	for(i = 0; i < scm; i++){		
		if (org[i] == match[0]) {
			
			for(j = 0; j < matchlength; j++){	//1文字目の一致
				if (org[i+j] != match[j]) {
					break;			//ハズレ
				}
				if ((org[i+j] == match[j]) & (j == matchlength - 1)) {
					srchresult++;	//発見
					break;
				}
			}
		}
	}

	if (srchresult == 1){
		printf("文字列\"%s\"が見つかりました。\n", match);
	}else if(srchresult > 1){
		printf("文字列\"%s\"が%d個見つかりました。\n", match, srchresult);
	}else{
		printf("文字列は見つかりませんでした。\n");
	}

	return 0;
}


//文字列の長さを調べる
int Strlength(const char* s){
	int n = 0;
	
	while (*s != '\0'){
		s++; n++;
	}
	return (n);
}


//エラーメッセージ
void errmsg(int chk){
	switch (chk){
	  case 0:
		break;
	  case 1:
		printf("引数が不正です。\n");
		break;
	  case 2:
		printf("検索文字列が探索文字列より長いです。\n");
		break;
	  default:
		printf("不正なエラーです。\n");
		break;
	}
}