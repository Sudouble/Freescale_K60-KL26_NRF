#include "NRF_SmartCar.h"

//下面这个函数是预留的接口，只需要将你的数据按照格式放进来就可以了

//data--要发送的数据 ；actualLen--需要发送数据的长度；sendlen，一次性发送的长度 (定值)：DATA_PACKET - 1 = 31
void SendPack_Long(unsigned char *data, int actualLen, int sendlen)
{
  //test
  //int count = 0;
  //=====

  uint8 buffer[DATA_PACKET] = {0};
  
  if (data != NULL && sendlen < DATA_PACKET)
  {
    //int send_length = strlen((char*)data);

    for (int i = 0; i < actualLen; i++)
    {
      buffer[i % sendlen + 1] = data[i];

      if ((i% sendlen + 1== sendlen))
      {
        buffer[0] = sendlen;
        if(nrf_tx(buffer, DATA_PACKET)==1)
        {
          while(nrf_tx_state() == NRF_TXING);         //等待发送完成
        }
        memset(buffer, 0, sizeof(buffer) / sizeof(char));
      }
      if ((i == actualLen - 1) && actualLen%sendlen != 0)
      {
        //添加结束符？
        buffer[0] = i % sendlen + 1;
        if(nrf_tx(buffer, DATA_PACKET)==1)
        {
          while(nrf_tx_state() == NRF_TXING);         //等待发送完成
        }
        memset(buffer, 0, sizeof(buffer) / sizeof(char));
      }

      //Do your job here
      //Dosomething();
    }
  }
  else
  {
    //reporte an error
  }
}


//value全部放大1000倍后回发电脑；（float报错也是醉了————万恶的IAR）
void SendPack_Short(int father, int child, float value, int hasHead, int hasEnd)
{
    char buffer[DATA_PACKET];
    char value_string[20];
    int count_i = 0;
    
    sprintf(value_string, "%4d|", (int)(1000*value));
    buffer[count_i++]='0';
    
    if(hasHead) //设置是否需要加数据头
      buffer[count_i++]='#';
    
    buffer[count_i++]='|';
    if(father > 10)
    {
        buffer[count_i++]=48 + father/10;
        buffer[count_i++]=48 + father%10;
    }
    else
    {
        buffer[count_i++]=48 + father;
    }
    buffer[count_i++]='|';
    
    //child 为两位，分情况进行添加
    if(child > 10)
    {
        buffer[count_i++]=48 + child/10;
        buffer[count_i++]=48 + child%10;
    }
    else
    {
        buffer[count_i++]=48 + child;
    }
    buffer[count_i++]='|';
    buffer[count_i++]='\0';
    strcat(buffer, value_string);
    if(hasEnd)  //添加结束符
      strcat(buffer, "$");
    buffer[0]=strlen(buffer)-1;
    
    //printf("%d---%s", (int)buffer[0], buffer);
    if(buffer[0] < 31)
    {
        if(nrf_tx((uint8*)buffer, DATA_PACKET)==1)
        {
            while(nrf_tx_state() == NRF_TXING);         //等待发送完成
        }
    }
    else
    {
        printf("in NRF_DIY.c of \"SendPack_Short\" is overflow!!");
    }
}
      
//value全部放大1000倍后回发电脑；（float报错也是醉了————万恶的IAR）
void SendPack_Echo(int father, int child, char *sendACK)
{
    char buffer[DATA_PACKET];
    int count_i = 0;
    
    buffer[count_i++]='0';
    
    buffer[count_i++]='#';
    
    buffer[count_i++]='|';
    if(father > 10)
    {
        buffer[count_i++]=48 + father/10;
        buffer[count_i++]=48 + father%10;
    }
    else
    {
        buffer[count_i++]=48 + father;
    }
    buffer[count_i++]='|';
    
    //child 为两位，分情况进行添加
    if(child > 10)
    {
        buffer[count_i++]=48 + child/10;
        buffer[count_i++]=48 + child%10;
    }
    else
    {
        buffer[count_i++]=48 + child;
    }
    buffer[count_i++]='|';
    buffer[count_i++]='\0';
    strcat(buffer, sendACK);
      strcat(buffer, "|$");
    buffer[0]=strlen(buffer)-1;
    
    //printf("%d---%s", (int)buffer[0], buffer);
    if(buffer[0] < 31)
    {
        if(nrf_tx((uint8*)buffer, DATA_PACKET)==1)
        {
            while(nrf_tx_state() == NRF_TXING);         //等待发送完成
        }
    }
    else
    {
        printf("in NRF_DIY.c of \"SendPack_Short\" is overflow!!");
    }
}

void SendPack_PID(int father, int child, float P, float I, float D, int hasHead, int hasEnd)//一次发送只能小于32为的数组
{
    char buffer[DATA_PACKET];
    char value_string[20];
    int count_i = 0;
    
    //============================================
    buffer[count_i++]='0';
    
    if(hasHead) //设置是否需要加数据头
      buffer[count_i++]='#';
    
    buffer[count_i++]='|';
    //数字大于10时候的单独处理
    if(father > 10)
    {
        buffer[count_i++]=48 + father/10;
        buffer[count_i++]=48 + father%10;
    }
    else
    {
        buffer[count_i++]=48 + father;
    }
    buffer[count_i++]='|';
    
    //child 为两位，分情况进行添加
    if(child > 10)
    {
        buffer[count_i++]=48 + child/10;
        buffer[count_i++]=48 + child%10;
    }
    else
    {
        buffer[count_i++]=48 + child;
    }
    buffer[count_i++]='|';
    buffer[count_i++]='\0';
    //添加P
    sprintf(value_string, "P%4d", (int)(1000*P));
    strcat(buffer, value_string);
    //添加I
    sprintf(value_string, "I%4d", (int)(1000*I));
    strcat(buffer, value_string);
    //添加D
    sprintf(value_string, "D%4d|", (int)(1000*D));
    strcat(buffer, value_string);
    
    if(hasEnd)  //添加结束符
      strcat(buffer, "$");
    
    buffer[0]=strlen(buffer)-1;
    
    //printf("%d---%s", (int)buffer[0], buffer);
    if(buffer[0] < 31)
    {
        if(nrf_tx((uint8*)buffer, DATA_PACKET)==1)
        {
            while(nrf_tx_state() == NRF_TXING);         //等待发送完成
        }
    }
    else
    {
        printf("in NRF_DIY.c of \"SendPack_Short\" is overflow!!");
    }
}

void SendPack_CCD(int father, int child, uint8 *ccdbuff, int ccdwidth, int hasHead, int hasEnd)//一次发送只能小于32为的数组
{
    char buffer[DATA_PACKET];
    char buff_end[DATA_PACKET];
    int count_i = 0;
    
    //============================================
    buffer[count_i++]='0';
    
    if(hasHead) //设置是否需要加数据头
      buffer[count_i++]='#';
    
    buffer[count_i++]='|';
    //数字大于10时候的单独处理
    if(father > 10)
    {
        buffer[count_i++]=48 + father/10;
        buffer[count_i++]=48 + father%10;
    }
    else
    {
        buffer[count_i++]=48 + father;
    }
    buffer[count_i++]='|';
    
    //child 为两位，分情况进行添加
    if(child > 10)
    {
        buffer[count_i++]=48 + child/10;
        buffer[count_i++]=48 + child%10;
    }
    else
    {
        buffer[count_i++]=48 + child;
    }
    buffer[count_i++]='|';
    
    //CCD发送格式
    buffer[count_i++]='(';
    //child 为两位，分情况进行添加
    if(ccdwidth > 100)
    {
        buffer[count_i++]=48 + ccdwidth/100;
        buffer[count_i++]=48 + ccdwidth/10%10;
        buffer[count_i++]=48 + ccdwidth%10;
    }
    else if(ccdwidth >10)
    {
        buffer[count_i++]=48 + ccdwidth/10;
        buffer[count_i++]=48 + ccdwidth%10;
    }
    else{}
    buffer[count_i++]=')';
    buffer[count_i++]='\0';
    buffer[0]=strlen(buffer) - 1;
    
    //NRF send buffer
    if(buffer[0] < 31)
    {
        if(nrf_tx((uint8*)buffer, DATA_PACKET)==1)
        {
            while(nrf_tx_state() == NRF_TXING);         //等待发送完成
        }
    }
    else
    {
        printf("in NRF_DIY.c of \"SendPack_Short\" is overflow!!");
    }
    
    //CCD数据的发送
    SendPack_Long(ccdbuff, ccdwidth, 31);
    
    count_i = 0;
    buff_end[count_i++]=1;
    buff_end[count_i++]='|';
    buff_end[count_i++]='\0';
    buff_end[0]=strlen(buff_end) - 1;
    
    //NRF send buffer
    if(buff_end[0] < 31)
    {
        if(nrf_tx((uint8*)buff_end, DATA_PACKET)==1)
        {
            while(nrf_tx_state() == NRF_TXING);         //等待发送完成
        }
    }
    
    count_i = 0;
    buff_end[count_i++]=1;
    buff_end[count_i++]='$';
    buff_end[count_i++]='\0';
    
    if(hasEnd)  //添加结束符
    {
        if(nrf_tx((uint8*)buff_end, DATA_PACKET)==1)
          {
              while(nrf_tx_state() == NRF_TXING);         //等待发送完成
          }
    }
    
    //printf("%d---%s", (int)buffer[0], buffer);
}

int NRF_Recieve(unsigned char *data, PIDSetting *pidsetting, int num_PID, DIYParameter *diypara,int numDIY, WholeSetting *wholesetting, int numWhole)//OK
{
    char i = 0, j = 0, maxJcount = 0;
    int Rxlen;
    int actual = 0;
    int Pos[50] = {0};
    
    //获取传参进来的结构体大小
    int size_pidsetting = num_PID;
    int size_diypara = numDIY;
    int size_wholesetting = numWhole;
    
    //解析后存放的值
    int father, child;
    float value_P, value_I, value_D, value;
    
    //以下进行数据的解析
    if (NULL != data)
    {
        Rxlen = strlen((char*)data);
        if (data[1] == '#'&& data[Rxlen - 1] == '$')
        {
            //以下为判断回路的值是否大于10；大于需要另外解析
            //length_count 的作用是判断 '|' 之间数的长度
            for (i = 0; i < Rxlen; i++)
            {
                if (data[i] == '|')
                {
                    Pos[j] = i;
                    j++;
                }
            }
            //获取真实的数据包数量
            maxJcount = j;
            j = 0;

            //actual = atof_self(data, Pos[j] + 1, Pos[j + 1]);
            //end
            for (j = 0; j < maxJcount; j++)
            {
                //  0 1 2 3    45 6 7               8
                //0#|2|2|1|3.31||1|1|P1200I2100D3310|$
                if ((j) % 4 == 0)
                {
                    father = atoi_self(data, Pos[j] + 1, Pos[j + 1]);
                }
                else if ((j) % 4 == 1)
                {
                    child = atoi_self(data, Pos[j] + 1, Pos[j + 1]);
                }
                else if ((j) % 4 == 2 && father == 1)  //PID参数
                {
                    //value = atof_self(data, Pos[j] + 1, Pos[j + 1]);
                    int Index_P;
                    int Index_I;
                    int Index_D;
                    for (int i = Pos[j] + 1; i < Pos[j + 1]; ++i)
                    {
                            if (data[i] == 'P')
                            {
                                    Index_P = i;
                                    continue;
                            }
                            if (data[i] == 'I')
                            {
                                    Index_I = i;
                                    continue;
                            }
                            if (data[i] == 'D')
                            {
                                    Index_D = i;
                                    continue;
                            }
                    }
                    value_P = atof_self(data, Index_P + 1, Index_I) / 1000.0;
                    value_I = atof_self(data, Index_I + 1, Index_D) / 1000.0;
                    value_D = atof_self(data, Index_D + 1, Pos[j + 1]) / 1000.0;
                    
                    printf("recv P: %d\n",atof_self(data, Index_P + 1, Index_I));

                    //判断是否数组越界
                    if(size_pidsetting >= child )
                    {
                        //将值保存至结构体
                        pidsetting[child - 1].FlagValueChanged = 1;
                        pidsetting[child - 1].father = father;
                        pidsetting[child - 1].child = child;
                        pidsetting[child - 1].Value_P = value_P;
                        pidsetting[child - 1].Value_I = value_I;
                        pidsetting[child - 1].Value_D = value_D;
                    }
                    else
                    {
                        printf("in NRF_DIY \"Unpackage\" pidsetting overflow !!");
                        return 0;
                    }
                }
                else if ((j) % 4 == 2 && father == 2)  //正常情况下的参数(自定义参数)
                {
                    value = atof_self(data, Pos[j] + 1, Pos[j + 1]) / 1000.0;

                    if(size_diypara >= child )
                    {
                        diypara[child - 1].FlagValueChanged = 1;
                        diypara[child - 1].father = father;
                        diypara[child - 1].child = child;
                        diypara[child - 1].DIY_Value = value;
                    }
                    else
                    {
                        printf("in NRF_DIY \"Unpackage\" diypara overflow !!");
                        return 0;
                    }
                }
                else if ((j) % 4 == 2 && father == 3)  //需要获取下面的参数并回发
                {
                    value = atof_self(data, Pos[j] + 1, Pos[j + 1]) / 1000.0;
                    
                    if(size_diypara >= child && value == 0)
                    {
                        wholesetting[child - 1].FlagValueChanged = 1;
                        wholesetting[child - 1].father = father;
                        wholesetting[child - 1].child = child;
                        wholesetting[child - 1].need_Send = 1;
                    }
                    else
                    {
                        printf("in NRF_DIY \"Unpackage\" wholesetting overflow !!");
                        return 0;
                    }
                }
                else
                {
                }
            }
        }
        return 1;     
    }
    return 0;
}

float atof_self(const unsigned char *str, int start, int end)
{
    const unsigned char *temp = str;
    int i = 0;
    int flags = 0;
    float sum = 0;
    while (i < start)
    {
        ++temp;
        ++i;
    }
    if (*temp != '-' && *temp != '+' && (*temp < '0' || *temp > '9')){//第一个字符不是数字
        return 0;
    }

    if (*temp == '-'){ //第一个是负号
        flags = 1;
        ++temp;
    }
    else if (*temp == '+'){
        ++temp;
    }

    i = 0;
    while (*temp >= '0' && *temp <= '9' && i < end){
        sum = sum * 10 + (*temp - '0');
        ++temp;
        ++i;
    }

    //if(flags){
    //sum *= -1;
    //}
    return flags ? (-1 * sum) : sum;
}

int atoi_self(const unsigned char *str, int start, int end)
{
    const unsigned char *temp = str;
    int i = 0;
    int flags = 0;
    unsigned int sum = 0;
    while (i < start)
    {
        ++temp;
        ++i;
    }
    if (*temp != '-' && *temp != '+' && (*temp < '0' || *temp > '9')){//第一个字符不是数字
        return 0;
    }

    if (*temp == '-'){ //第一个是负号
        flags = 1;
        ++temp;
    }
    else if (*temp == '+'){
        ++temp;
    }

    i = 0;
    while (*temp >= '0' && *temp <= '9' && i < end){
        if (!flags){//上溢
            if (sum > MAX_INT / 10 || (sum == MAX_INT / 10 && (*temp > '7'))){
                return MAX_INT;
            }

        }
        else{//下溢
            if (sum > MAX_INT / 10 || (sum == MAX_INT / 10 && (*temp > '8'))){
                return MIN_INT;
            }
        }

        sum = sum * 10 + (*temp - '0');
        ++temp;
        ++i;
    }

    //if(flags){
    //sum *= -1;
    //}
    return flags ? (-1 * sum) : sum;
}
