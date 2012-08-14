#include <iostream>

#ifndef CLASS_SOCK_STREAM_BUF
#define CLASS_SOCK_STREAM_BUF
//ソケットを渡して、読み出すだけ、書き出すだけをするStreamBuf.
//バッファがフラッシュされるときにはrecvやsendの返り値が返る
class SocketStreamBuf : public std::streambuf
{
    //読み取りデータバッファ
    char readbuf[1025];
    //書き込みデータバッファ
    char writebuf[1025];
    //接続先ソケット
    int sockfd;
public:
    //コンストラクタ
    SocketStreamBuf(int sock);
    
    //デストラクタ
    //ソケットを閉じるのに失敗するとexitします
    ~SocketStreamBuf();
    
    //sync, overflow, underflowの３つはバッファからソケットに書き込んだバイト数を返します
    virtual int sync();

    virtual int overflow();

    virtual int underflow();
};

#endif
