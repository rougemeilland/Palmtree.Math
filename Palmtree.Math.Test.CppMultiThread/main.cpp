// ModPow の多重実行時にアクセス違反例外でこける障害の調査プログラム
// 残念ながら再現しない
// 発生条件にc#も絡む可能性がある。


#include <atomic>
#include <iostream>
#include <clocale>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "pmc.h"
#include "pmc_uint_cppinterface.h"
#include "pmc_sint_cppinterface.h"
#include "pmc_rtnl_cppinterface.h"

#define countof(x)  (sizeof(x)/sizeof(*(x)))

namespace Palmtree::Math::Core::Internal
{
    unsigned char data_item_0[] = { 0x00, 0x00 };
    unsigned char data_item_1[] = { 0x01, 0x01, 0x01 };
    unsigned char data_item_2[] = { 0x01, 0x04, 0xd2, 0x02, 0x96, 0x49 };
    unsigned char data_item_3[] = { 0x01, 0x04, 0xff, 0xff, 0xff, 0xff };
    unsigned char data_item_4[] = { 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01 };
    unsigned char data_item_5[] = { 0x01, 0x05, 0xff, 0xe3, 0x0b, 0x54, 0x02 };
    unsigned char data_item_6[] = { 0x01, 0x08, 0xd2, 0x0a, 0x1f, 0xeb, 0x8c, 0xa9, 0x54, 0xab };
    unsigned char data_item_7[] = { 0x01, 0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    unsigned char data_item_8[] = { 0x01, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    unsigned char data_item_9[] = { 0x01, 0x09, 0xff, 0xff, 0x0f, 0x63, 0x2d, 0x5e, 0xc7, 0x6b, 0x05 };
    unsigned char data_item_10[] = { 0x01, 0x11, 0xd2, 0x0a, 0x3f, 0xce, 0x96, 0x5f, 0xbc, 0xac, 0xb8, 0xf3, 0xdb, 0xc0, 0x75, 0x20, 0xc9, 0xa0, 0x03 };
    unsigned char data_item_11[] = { 0x01, 0x11, 0xff, 0xff, 0xff, 0xff, 0xff, 0x60, 0xf5, 0xb9, 0xab, 0xbf, 0xa4, 0x5c, 0xc3, 0xf1, 0x29, 0x63, 0x1d };
    unsigned char data_item_12[] = { 0x01, 0x21, 0xd2, 0x0a, 0x3f, 0xce, 0x96, 0xf1, 0xcf, 0xac, 0x4b, 0xf1, 0x29, 0xcb, 0x1d, 0xa1, 0x6a, 0x6d, 0x15, 0x7f, 0x09, 0xb4, 0x68, 0x92, 0xad, 0x31, 0x8f, 0x22, 0x3c, 0xb6, 0x3c, 0xa2, 0x8e, 0x9e, 0x6a };
    unsigned char data_item_13[] = { 0x01, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xce, 0x64, 0x27, 0xa2, 0x63, 0xca, 0x18, 0xa4, 0xef, 0x25, 0x7b, 0xd1, 0xcd, 0x70, 0xef, 0xdf, 0x6b, 0x1f, 0x3e, 0xea, 0x9d, 0x5f, 0x03 };
    unsigned char data_item_14[] = { 0x01, 0x43, 0xd2, 0x0a, 0x3f, 0xce, 0x96, 0xf1, 0xcf, 0xac, 0x4b, 0xf1, 0x7b, 0xef, 0x61, 0x11, 0x3d, 0x24, 0x5e, 0x93, 0xa9, 0x88, 0x45, 0x42, 0x21, 0xdb, 0x9c, 0x0c, 0x9b, 0xde, 0xc4, 0x1f, 0xc6, 0x58, 0xcf, 0xf4, 0x5a, 0xd1, 0xcc, 0xd6, 0xfc, 0xc7, 0xa6, 0x32, 0x88, 0xea, 0x83, 0x91, 0xc5, 0x0a, 0xa6, 0x20, 0x1d, 0x29, 0xa6, 0xc5, 0x44, 0x75, 0x6f, 0xc3, 0x13, 0x88, 0x06, 0x32, 0xa1, 0x47, 0xae, 0x67, 0x01 };
    unsigned char data_item_15[] = { 0x01, 0x43, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x2d, 0xc3, 0xfb, 0xf4, 0xd0, 0x22, 0x52, 0x50, 0x28, 0x0f, 0xb7, 0xf3, 0xf2, 0x13, 0x57, 0x13, 0x14, 0x42, 0xdc, 0x7d, 0x5d, 0x39, 0xd6, 0x99, 0x19, 0x59, 0xf8, 0x1c, 0x38, 0x92, 0x00, 0xd6, 0x14, 0xb3, 0x86, 0xb9, 0x77, 0xa5, 0x7a, 0x61, 0xfe, 0xb7, 0x12, 0x6a, 0x61, 0x0b };

    struct DataItem
    {
        unsigned char* Data;
        size_t DataCount;
    };

    static DataItem* data_items;

    static Palmtree::Math::Core::Internal::PMC_UINT_CppInterface ep_uint;
    static Palmtree::Math::Core::Internal::PMC_SINT_CppInterface ep_sint;
    static Palmtree::Math::Core::Internal::PMC_RTNL_CppInterface ep_rtnl;

    static void initialize()
    {
        std::setlocale(LC_CTYPE, "ja-JP");

        data_items = new DataItem[16];

        data_items[0].Data = data_item_0;
        data_items[0].DataCount = countof(data_item_0);

        data_items[1].Data = data_item_1;
        data_items[1].DataCount = countof(data_item_1);

        data_items[2].Data = data_item_2;
        data_items[2].DataCount = countof(data_item_2);

        data_items[3].Data = data_item_3;
        data_items[3].DataCount = countof(data_item_3);

        data_items[4].Data = data_item_4;
        data_items[4].DataCount = countof(data_item_4);

        data_items[5].Data = data_item_5;
        data_items[5].DataCount = countof(data_item_5);

        data_items[6].Data = data_item_6;
        data_items[6].DataCount = countof(data_item_6);

        data_items[7].Data = data_item_7;
        data_items[7].DataCount = countof(data_item_7);

        data_items[8].Data = data_item_8;
        data_items[8].DataCount = countof(data_item_8);

        data_items[9].Data = data_item_9;
        data_items[9].DataCount = countof(data_item_9);

        data_items[10].Data = data_item_10;
        data_items[10].DataCount = countof(data_item_10);

        data_items[11].Data = data_item_11;
        data_items[11].DataCount = countof(data_item_11);

        data_items[12].Data = data_item_12;
        data_items[12].DataCount = countof(data_item_12);

        data_items[13].Data = data_item_13;
        data_items[13].DataCount = countof(data_item_13);

        data_items[14].Data = data_item_14;
        data_items[14].DataCount = countof(data_item_14);

        data_items[15].Data = data_item_15;
        data_items[15].DataCount = countof(data_item_15);

        ep_uint.Initialize();
        ep_sint.Initialize();
        ep_rtnl.Initialize();
    }

    static bool ready = false;
    static std::mutex mtx;
    static std::condition_variable cv;
    static std::atomic<int> total_count;

    static void thread_func()
    {
        {
            std::unique_lock<std::mutex> lk(mtx);
            cv.wait(lk, [&] { return (ready); });
        }

        for (int count = 0; count < 16; ++count)
        {

            for (int v_index = 0; v_index < 16; ++v_index)
            {
                for (int e_index = 0; e_index < 16; ++e_index)
                {
                    for (int m_index = 0; m_index < 16; ++m_index)
                    {
                        if (m_index == 0)
                        {
                            // 0 除算例外が発生してしまうので nop
                        }
                        else if (v_index == 0 && e_index == 0)
                        {
                            // 0 の 0 乗は未定義なので nop
                        }
                        else
                        {
                            PMC_HANDLE_UINT v = ep_uint.FromByteArray_UINT(data_items[v_index].Data, data_items[v_index].DataCount);
                            PMC_HANDLE_UINT e = ep_uint.FromByteArray_UINT(data_items[e_index].Data, data_items[e_index].DataCount);
                            PMC_HANDLE_UINT m = ep_uint.FromByteArray_UINT(data_items[m_index].Data, data_items[m_index].DataCount);
                            PMC_HANDLE_UINT r = ep_uint.ModPow(v, e, m);
                            unsigned char r_buf[256];
                            ep_uint.ToByteArray(r, r_buf, countof(r_buf));
                            ep_uint.Dispose(v);
                            ep_uint.Dispose(e);
                            ep_uint.Dispose(m);
                            ep_uint.Dispose(r);
                            ++total_count;
                        }
                    }
                }
            }
        }
    }


    extern "C" int main()
    {
        Palmtree::Math::Core::Internal::initialize();

        std::thread t0(Palmtree::Math::Core::Internal::thread_func);
        std::thread t1(Palmtree::Math::Core::Internal::thread_func);
        std::thread t2(Palmtree::Math::Core::Internal::thread_func);
        std::thread t3(Palmtree::Math::Core::Internal::thread_func);
        std::thread t4(Palmtree::Math::Core::Internal::thread_func);
        std::thread t5(Palmtree::Math::Core::Internal::thread_func);
        std::thread t6(Palmtree::Math::Core::Internal::thread_func);
        std::thread t7(Palmtree::Math::Core::Internal::thread_func);
        {
            std::lock_guard<std::mutex> lk(mtx);
            ready = true;
            cv.notify_all();
        }

        t0.join();
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();

        wchar_t temp[256];
        swprintf_s(temp, countof(temp), L"%d", total_count.load());
        std::wcout << L"計算回数=" << temp  << std::endl;
        return (0);
    }

}
