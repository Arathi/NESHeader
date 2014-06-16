#ifndef __NES_HEADER__
#define __NES_HEADER__

#include <string>
#include <sstream>
using namespace std;

class NESHeader
{
public:
    NESHeader(unsigned char header_bytes[16])
    {
        init(header_bytes);
    }
    
    ~NESHeader()
    {
        //目前没有什么需要释放掉的
    }
    
    void init(unsigned char header_bytes[16])
    {
        //NES^Z
        format[0]=header_bytes[0];
        format[1]=header_bytes[1];
        format[2]=header_bytes[2];
        format[3]=header_bytes[3];
        //ROM大小
        prom_amount=header_bytes[4];
        vrom_amount=header_bytes[5];
        //功能混合字节
        char byte6 = header_bytes[6];
        char byte7 = header_bytes[7];
        vertical_mirror = (byte6 & 0x01)!=0x00;
        battery_memory = (byte6 & 0x02)!=0x00;
        trainer = (byte6 & 0x04)!=0x00;
        four_screen = (byte6 & 0x08)!=0x00;
        char mapper_low4bits = (byte6 >> 4);
        char mapper_high4bits = (byte7 & 0xF0);
        mapper_id = mapper_low4bits | mapper_high4bits;
        //保留字节
        int i;
        for (i=0; i<8; i++)
        {
            reserved[i]=header_bytes[8+i];
        }
    }
    
    bool is_valid()
    {
        //检查文件格式说明符(NES^Z)
        if (
            format[0]!='N' ||
            format[1]!='E' ||
            format[2]!='S' ||
            format[3]!=0x1A )
        {
            cerr<<"文件格式说明符不为NES^Z"<<endl;
            return false;
        }
        //检查副Mapper
        if (mapper_id_extension!=0x00)
        {
            cerr<<"非法的副Mapper"<<endl;
            return false;
        }
        //检查8个保留字节
        int i;
        for (i=0; i<8; i++)
        {
            if (reserved[i]!=0x00)
            {
                cerr<<"非法的保留字节"<<endl;
                return false;
            }
        }
        return true;
    }
    
    /**
     * 获取PROM数量
     */
    int get_prom_amount()
    {
        return prom_amount;
    }
    
    /**
     * 获取VROM数量
     */
    int get_vrom_amount()
    {
        return vrom_amount;
    }
    
    /**
     * 是否为垂直镜像
     * true: 垂直镜像
     * false: 水平镜像
     */
    bool is_vertical_mirror()
    {
        return vertical_mirror;
    }
    
    /**
     * 是否有电池记忆
     */
    bool has_battery_memory()
    {
        return battery_memory;
    }
    
    /**
     * 是否存在$200个字节的trainer
     */
    bool has_trainer()
    {
        return trainer;
    }
    
    /**
     * 是否为4屏幕VRAM布局
     */
    bool is_four_screen()
    {
        return four_screen;
    }
    
    /**
     * 输出ROM的信息
     */
    string to_string()
    {
        stringstream line;
        string resultLine;
        string result="";
        if ( !is_valid() )
        {
            return "该文件不是合法的iNES格式的ROM！";
        }
        line<<"合法ROM";
        line>>resultLine;
        line.clear();
        result+=resultLine+"\n";
        
        line<<"PROM数量："<<(int) prom_amount;
        line>>resultLine;
        line.clear();
        result+=resultLine+"\n";
        
        line<<"VROM数量："<<(int) vrom_amount;
        line>>resultLine;
        line.clear();
        result+=resultLine+"\n";
        
        if ( is_vertical_mirror() )
        {
            line<<"垂直";
        }
        else
        {
            line<<"水平";
        }
        line<<"镜像";
        if ( is_four_screen() )
        {
            line<<" (四屏幕布局)";
        }
        line>>resultLine;
        line.clear();
        result+=resultLine+"\n";
        
        if ( has_battery_memory() )
        {
            line<<"有";
        }
        else
        {
            line<<"无";
        }
        line<<"电池记忆";
        line>>resultLine;
        line.clear();
        result+=resultLine+"\n";
        
        if ( has_trainer() )
        {
            line<<"有";
        }
        else
        {
            line<<"无";
        }
        line<<"Trainer";
        line>>resultLine;
        line.clear();
        result+=resultLine+"\n";
        
        line<<"Mapper编号："<<(int) mapper_id;
        line>>resultLine;
        line.clear();
        result+=resultLine+"\n";
        
        return result;
    }

private:
    unsigned char format[4]; //格式说明符NES^Z
    unsigned char prom_amount; //16k PROM 数量
    unsigned char vrom_amount; //8k VROM 数量
    bool vertical_mirror; //是否为垂直镜像
    bool battery_memory; //是否有电池记忆
    bool trainer; //在$7000-$71FF存在$200个字节的trainer
    bool four_screen; //是否为4屏幕VRAM布局
    unsigned char mapper_id; //Mapper编号
    unsigned char mapper_id_extension; //扩展Mapper编号
    unsigned char reserved[8]; //8个保留字节
};

#endif 
