#include"finesse.h"
#include <cstring>
#include <iostream>
#include <xxhash.h>
using namespace std;


int main(void){
    
    //进行Finesse各参数的初始化
    int BLOCK_SIZE = 4096; //chunk的大小
    int SF_WINDOW = 48; //滑动窗口大小
    int SF_NUM = 3; //SF个数
    int FEATURE_NUM = 12; //Feature个数
    Finesse lsh(BLOCK_SIZE,SF_WINDOW, SF_NUM, FEATURE_NUM); //Finesse对象初始化
    uint64_t* sf_temp;
    sf_temp = new uint64_t[SF_NUM];
    //创建第一个chunk data
    uint8_t* temp_chunk;
    temp_chunk = (uint8_t*)malloc(4096);
    memset(temp_chunk,0,4096);
    //计算第一个chunk data的FP
    XXH64_hash_t h = XXH64(temp_chunk, 4096, 0);
    printf("the first chunk FP:%d\n",h);
    //计算第一个chunk data的SF
    lsh.getSF((unsigned char*)temp_chunk,sf_temp);
    //查找第一个chunk data是否存在相似的chunk
    XXH64_hash_t tempflag = lsh.find(sf_temp);
    //返回值为-1 说明没有相似chunk
    printf("there is no basechunk: %d\n",tempflag);
    //第一个chunk作为basechunk 更新SF_map
    lsh.insert(h);
    //创建第二个chunk data，与第一个chunk data仅[0]不同
    uint8_t* temp_chunk2;
    temp_chunk2 = (uint8_t*)malloc(4096);
    memset(temp_chunk2,0,4096);
    memset(temp_chunk2,1,1);
    //计算第二个chunk data的FP和SF
    XXH64_hash_t h2 = XXH64(temp_chunk2, 4096, 0);
    lsh.getSF((unsigned char*)temp_chunk2,sf_temp);
    //查找第而个chunk data是否存在相似的chunk
    tempflag = lsh.find(sf_temp);
    //返回值为第一个chunk的hash，chunk1为chunk2的相似chunk
    printf("the basechunk FP: %d\n",tempflag);

    delete sf_temp;
    free(temp_chunk1);
    free(temp_chunk2);
    return 0;
}