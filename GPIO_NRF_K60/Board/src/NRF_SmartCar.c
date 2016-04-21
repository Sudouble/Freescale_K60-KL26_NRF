#include "NRF_SmartCar.h"

//�������������Ԥ���Ľӿڣ�ֻ��Ҫ��������ݰ��ո�ʽ�Ž����Ϳ�����

//data--Ҫ���͵����� ��actualLen--��Ҫ�������ݵĳ��ȣ�sendlen��һ���Է��͵ĳ��� (��ֵ)��DATA_PACKET - 1 = 31
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
          while(nrf_tx_state() == NRF_TXING);         //�ȴ��������
        }
        memset(buffer, 0, sizeof(buffer) / sizeof(char));
      }
      if ((i == actualLen - 1) && actualLen%sendlen != 0)
      {
        //��ӽ�������
        buffer[0] = i % sendlen + 1;
        if(nrf_tx(buffer, DATA_PACKET)==1)
        {
          while(nrf_tx_state() == NRF_TXING);         //�ȴ��������
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


//valueȫ���Ŵ�1000����ط����ԣ���float����Ҳ�����ˡ�����������IAR��
void SendPack_Short(int father, int child, float value, int hasHead, int hasEnd)
{
    char buffer[DATA_PACKET];
    char value_string[20];
    int count_i = 0;
    
    sprintf(value_string, "%4d|", (int)(1000*value));
    buffer[count_i++]='0';
    
    if(hasHead) //�����Ƿ���Ҫ������ͷ
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
    
    //child Ϊ��λ��������������
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
    if(hasEnd)  //��ӽ�����
      strcat(buffer, "$");
    buffer[0]=strlen(buffer)-1;
    
    //printf("%d---%s", (int)buffer[0], buffer);
    if(buffer[0] < 31)
    {
        if(nrf_tx((uint8*)buffer, DATA_PACKET)==1)
        {
            while(nrf_tx_state() == NRF_TXING);         //�ȴ��������
        }
    }
    else
    {
        printf("in NRF_DIY.c of \"SendPack_Short\" is overflow!!");
    }
}
      
//valueȫ���Ŵ�1000����ط����ԣ���float����Ҳ�����ˡ�����������IAR��
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
    
    //child Ϊ��λ��������������
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
            while(nrf_tx_state() == NRF_TXING);         //�ȴ��������
        }
    }
    else
    {
        printf("in NRF_DIY.c of \"SendPack_Short\" is overflow!!");
    }
}

void SendPack_PID(int father, int child, float P, float I, float D, int hasHead, int hasEnd)//һ�η���ֻ��С��32Ϊ������
{
    char buffer[DATA_PACKET];
    char value_string[20];
    int count_i = 0;
    
    //============================================
    buffer[count_i++]='0';
    
    if(hasHead) //�����Ƿ���Ҫ������ͷ
      buffer[count_i++]='#';
    
    buffer[count_i++]='|';
    //���ִ���10ʱ��ĵ�������
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
    
    //child Ϊ��λ��������������
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
    //���P
    sprintf(value_string, "P%4d", (int)(1000*P));
    strcat(buffer, value_string);
    //���I
    sprintf(value_string, "I%4d", (int)(1000*I));
    strcat(buffer, value_string);
    //���D
    sprintf(value_string, "D%4d|", (int)(1000*D));
    strcat(buffer, value_string);
    
    if(hasEnd)  //��ӽ�����
      strcat(buffer, "$");
    
    buffer[0]=strlen(buffer)-1;
    
    //printf("%d---%s", (int)buffer[0], buffer);
    if(buffer[0] < 31)
    {
        if(nrf_tx((uint8*)buffer, DATA_PACKET)==1)
        {
            while(nrf_tx_state() == NRF_TXING);         //�ȴ��������
        }
    }
    else
    {
        printf("in NRF_DIY.c of \"SendPack_Short\" is overflow!!");
    }
}

void SendPack_CCD(int father, int child, uint8 *ccdbuff, int ccdwidth, int hasHead, int hasEnd)//һ�η���ֻ��С��32Ϊ������
{
    char buffer[DATA_PACKET];
    char buff_end[DATA_PACKET];
    int count_i = 0;
    
    //============================================
    buffer[count_i++]='0';
    
    if(hasHead) //�����Ƿ���Ҫ������ͷ
      buffer[count_i++]='#';
    
    buffer[count_i++]='|';
    //���ִ���10ʱ��ĵ�������
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
    
    //child Ϊ��λ��������������
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
    
    //CCD���͸�ʽ
    buffer[count_i++]='(';
    //child Ϊ��λ��������������
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
            while(nrf_tx_state() == NRF_TXING);         //�ȴ��������
        }
    }
    else
    {
        printf("in NRF_DIY.c of \"SendPack_Short\" is overflow!!");
    }
    
    //CCD���ݵķ���
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
            while(nrf_tx_state() == NRF_TXING);         //�ȴ��������
        }
    }
    
    count_i = 0;
    buff_end[count_i++]=1;
    buff_end[count_i++]='$';
    buff_end[count_i++]='\0';
    
    if(hasEnd)  //��ӽ�����
    {
        if(nrf_tx((uint8*)buff_end, DATA_PACKET)==1)
          {
              while(nrf_tx_state() == NRF_TXING);         //�ȴ��������
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
    
    //��ȡ���ν����Ľṹ���С
    int size_pidsetting = num_PID;
    int size_diypara = numDIY;
    int size_wholesetting = numWhole;
    
    //�������ŵ�ֵ
    int father, child;
    float value_P, value_I, value_D, value;
    
    //���½������ݵĽ���
    if (NULL != data)
    {
        Rxlen = strlen((char*)data);
        if (data[1] == '#'&& data[Rxlen - 1] == '$')
        {
            //����Ϊ�жϻ�·��ֵ�Ƿ����10��������Ҫ�������
            //length_count ���������ж� '|' ֮�����ĳ���
            for (i = 0; i < Rxlen; i++)
            {
                if (data[i] == '|')
                {
                    Pos[j] = i;
                    j++;
                }
            }
            //��ȡ��ʵ�����ݰ�����
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
                else if ((j) % 4 == 2 && father == 1)  //PID����
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

                    //�ж��Ƿ�����Խ��
                    if(size_pidsetting >= child )
                    {
                        //��ֵ�������ṹ��
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
                else if ((j) % 4 == 2 && father == 2)  //��������µĲ���(�Զ������)
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
                else if ((j) % 4 == 2 && father == 3)  //��Ҫ��ȡ����Ĳ������ط�
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
    if (*temp != '-' && *temp != '+' && (*temp < '0' || *temp > '9')){//��һ���ַ���������
        return 0;
    }

    if (*temp == '-'){ //��һ���Ǹ���
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
    if (*temp != '-' && *temp != '+' && (*temp < '0' || *temp > '9')){//��һ���ַ���������
        return 0;
    }

    if (*temp == '-'){ //��һ���Ǹ���
        flags = 1;
        ++temp;
    }
    else if (*temp == '+'){
        ++temp;
    }

    i = 0;
    while (*temp >= '0' && *temp <= '9' && i < end){
        if (!flags){//����
            if (sum > MAX_INT / 10 || (sum == MAX_INT / 10 && (*temp > '7'))){
                return MAX_INT;
            }

        }
        else{//����
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
