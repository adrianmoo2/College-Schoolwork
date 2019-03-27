/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/ise/virtualshare/Lab06/CS161L_Lab08/SPFPMult.v";
static unsigned int ng1[] = {1U, 0U};
static int ng2[] = {0, 0};
static int ng3[] = {48, 0};
static unsigned int ng4[] = {0U, 0U};
static int ng5[] = {1, 0};
static int ng6[] = {127, 0};



static void Always_53_0(char *t0)
{
    char t6[8];
    char t23[8];
    char t24[16];
    char t28[8];
    char t54[8];
    char t56[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    char *t25;
    unsigned int t26;
    char *t27;
    char *t29;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    char *t43;
    char *t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    char *t50;
    char *t51;
    char *t52;
    char *t53;
    char *t55;

LAB0:    t1 = (t0 + 6840U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(53, ng0);
    t2 = (t0 + 7408);
    *((int *)t2) = 1;
    t3 = (t0 + 6872);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(53, ng0);

LAB5:    xsi_set_current_line(55, ng0);
    t4 = (t0 + 1528U);
    t5 = *((char **)t4);
    memset(t6, 0, 8);
    t4 = (t6 + 4);
    t7 = (t5 + 4);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 31);
    t10 = (t9 & 1);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 31);
    t13 = (t12 & 1);
    *((unsigned int *)t4) = t13;
    t14 = (t0 + 2728);
    xsi_vlogvar_assign_value(t14, t6, 0, 0, 1);
    xsi_set_current_line(56, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 31);
    t10 = (t9 & 1);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 31);
    t13 = (t12 & 1);
    *((unsigned int *)t2) = t13;
    t5 = (t0 + 2888);
    xsi_vlogvar_assign_value(t5, t6, 0, 0, 1);
    xsi_set_current_line(58, ng0);
    t2 = (t0 + 2728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2888);
    t7 = (t5 + 56U);
    t14 = *((char **)t7);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t14);
    t10 = (t8 ^ t9);
    *((unsigned int *)t6) = t10;
    t15 = (t4 + 4);
    t16 = (t14 + 4);
    t17 = (t6 + 4);
    t11 = *((unsigned int *)t15);
    t12 = *((unsigned int *)t16);
    t13 = (t11 | t12);
    *((unsigned int *)t17) = t13;
    t18 = *((unsigned int *)t17);
    t19 = (t18 != 0);
    if (t19 == 1)
        goto LAB6;

LAB7:
LAB8:    t22 = (t0 + 3208);
    xsi_vlogvar_assign_value(t22, t6, 0, 0, 1);
    xsi_set_current_line(61, ng0);
    t2 = (t0 + 1528U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 0);
    *((unsigned int *)t6) = t9;
    t10 = *((unsigned int *)t4);
    t11 = (t10 >> 0);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t12 & 8388607U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 8388607U);
    t5 = (t0 + 3688);
    xsi_vlogvar_assign_value(t5, t6, 0, 0, 23);
    xsi_set_current_line(62, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 0);
    *((unsigned int *)t6) = t9;
    t10 = *((unsigned int *)t4);
    t11 = (t10 >> 0);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t12 & 8388607U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 8388607U);
    t5 = (t0 + 3848);
    xsi_vlogvar_assign_value(t5, t6, 0, 0, 23);
    xsi_set_current_line(64, ng0);
    t2 = (t0 + 3688);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    xsi_vlogtype_concat(t23, 23, 23, 1U, t4, 23);
    t5 = ((char*)((ng1)));
    xsi_vlogtype_concat(t6, 24, 24, 2U, t5, 1, t23, 23);
    t7 = (t0 + 4008);
    xsi_vlogvar_assign_value(t7, t6, 0, 0, 24);
    xsi_set_current_line(65, ng0);
    t2 = (t0 + 3848);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    xsi_vlogtype_concat(t23, 23, 23, 1U, t4, 23);
    t5 = ((char*)((ng1)));
    xsi_vlogtype_concat(t6, 24, 24, 2U, t5, 1, t23, 23);
    t7 = (t0 + 4168);
    xsi_vlogvar_assign_value(t7, t6, 0, 0, 24);
    xsi_set_current_line(67, ng0);
    t2 = (t0 + 4008);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 4168);
    t7 = (t5 + 56U);
    t14 = *((char **)t7);
    xsi_vlog_unsigned_multiply(t24, 48, t4, 24, t14, 24);
    t15 = (t0 + 5608);
    xsi_vlogvar_assign_value(t15, t24, 0, 0, 48);
    xsi_set_current_line(70, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5288);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(71, ng0);
    xsi_set_current_line(71, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5928);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);

LAB9:    t2 = (t0 + 5928);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng3)));
    memset(t6, 0, 8);
    xsi_vlog_signed_less(t6, 32, t4, 32, t5, 32);
    t7 = (t6 + 4);
    t8 = *((unsigned int *)t7);
    t9 = (~(t8));
    t10 = *((unsigned int *)t6);
    t11 = (t10 & t9);
    t12 = (t11 != 0);
    if (t12 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(78, ng0);
    t2 = (t0 + 5608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t7 = (t4 + 4);
    t8 = *((unsigned int *)t4);
    t9 = (t8 >> 23);
    *((unsigned int *)t6) = t9;
    t10 = *((unsigned int *)t7);
    t11 = (t10 >> 23);
    *((unsigned int *)t5) = t11;
    t14 = (t4 + 8);
    t15 = (t4 + 12);
    t12 = *((unsigned int *)t14);
    t13 = (t12 << 9);
    t18 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t18 | t13);
    t19 = *((unsigned int *)t15);
    t20 = (t19 << 9);
    t21 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t21 | t20);
    t26 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t26 & 16777215U);
    t31 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t31 & 16777215U);
    t16 = (t0 + 4488);
    xsi_vlogvar_assign_value(t16, t6, 0, 0, 24);
    xsi_set_current_line(81, ng0);
    t2 = (t0 + 1528U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 23);
    *((unsigned int *)t6) = t9;
    t10 = *((unsigned int *)t4);
    t11 = (t10 >> 23);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t12 & 255U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 255U);
    t5 = (t0 + 4648);
    xsi_vlogvar_assign_value(t5, t6, 0, 0, 8);
    xsi_set_current_line(82, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 23);
    *((unsigned int *)t6) = t9;
    t10 = *((unsigned int *)t4);
    t11 = (t10 >> 23);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t12 & 255U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 255U);
    t5 = (t0 + 4808);
    xsi_vlogvar_assign_value(t5, t6, 0, 0, 8);
    xsi_set_current_line(84, ng0);
    t2 = (t0 + 4648);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 4808);
    t7 = (t5 + 56U);
    t14 = *((char **)t7);
    memset(t6, 0, 8);
    xsi_vlog_unsigned_add(t6, 32, t4, 8, t14, 8);
    t15 = ((char*)((ng6)));
    memset(t23, 0, 8);
    xsi_vlog_unsigned_minus(t23, 32, t6, 32, t15, 32);
    t16 = (t0 + 4968);
    xsi_vlogvar_assign_value(t16, t23, 0, 0, 8);
    xsi_set_current_line(86, ng0);
    t2 = (t0 + 5288);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t6, 0, 8);
    t7 = (t4 + 4);
    t14 = (t5 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t5);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t7);
    t12 = *((unsigned int *)t14);
    t13 = (t11 ^ t12);
    t18 = (t10 | t13);
    t19 = *((unsigned int *)t7);
    t20 = *((unsigned int *)t14);
    t21 = (t19 | t20);
    t26 = (~(t21));
    t31 = (t18 & t26);
    if (t31 != 0)
        goto LAB24;

LAB21:    if (t21 != 0)
        goto LAB23;

LAB22:    *((unsigned int *)t6) = 1;

LAB24:    t16 = (t6 + 4);
    t32 = *((unsigned int *)t16);
    t33 = (~(t32));
    t34 = *((unsigned int *)t6);
    t35 = (t34 & t33);
    t36 = (t35 != 0);
    if (t36 > 0)
        goto LAB25;

LAB26:
LAB27:    xsi_set_current_line(90, ng0);
    t2 = (t0 + 4488);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t28, 0, 8);
    t5 = (t28 + 4);
    t7 = (t4 + 4);
    t8 = *((unsigned int *)t4);
    t9 = (t8 >> 1);
    *((unsigned int *)t28) = t9;
    t10 = *((unsigned int *)t7);
    t11 = (t10 >> 1);
    *((unsigned int *)t5) = t11;
    t12 = *((unsigned int *)t28);
    *((unsigned int *)t28) = (t12 & 8388607U);
    t13 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t13 & 8388607U);
    xsi_vlogtype_concat(t23, 23, 23, 1U, t28, 23);
    t14 = (t0 + 4968);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    xsi_vlogtype_concat(t54, 8, 8, 1U, t16, 8);
    t17 = (t0 + 3208);
    t22 = (t17 + 56U);
    t25 = *((char **)t22);
    xsi_vlogtype_concat(t56, 1, 1, 1U, t25, 1);
    xsi_vlogtype_concat(t6, 32, 32, 3U, t56, 1, t54, 8, t23, 23);
    t27 = (t0 + 2568);
    xsi_vlogvar_assign_value(t27, t6, 0, 0, 32);
    xsi_set_current_line(91, ng0);
    t2 = (t0 + 2568);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2408);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 32);
    goto LAB2;

LAB6:    t20 = *((unsigned int *)t6);
    t21 = *((unsigned int *)t17);
    *((unsigned int *)t6) = (t20 | t21);
    goto LAB8;

LAB10:    xsi_set_current_line(71, ng0);

LAB12:    xsi_set_current_line(72, ng0);
    t14 = (t0 + 5608);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    memset(t23, 0, 8);
    t17 = (t23 + 4);
    t22 = (t16 + 8);
    t25 = (t16 + 12);
    t13 = *((unsigned int *)t22);
    t18 = (t13 >> 15);
    t19 = (t18 & 1);
    *((unsigned int *)t23) = t19;
    t20 = *((unsigned int *)t25);
    t21 = (t20 >> 15);
    t26 = (t21 & 1);
    *((unsigned int *)t17) = t26;
    t27 = ((char*)((ng4)));
    memset(t28, 0, 8);
    t29 = (t23 + 4);
    t30 = (t27 + 4);
    t31 = *((unsigned int *)t23);
    t32 = *((unsigned int *)t27);
    t33 = (t31 ^ t32);
    t34 = *((unsigned int *)t29);
    t35 = *((unsigned int *)t30);
    t36 = (t34 ^ t35);
    t37 = (t33 | t36);
    t38 = *((unsigned int *)t29);
    t39 = *((unsigned int *)t30);
    t40 = (t38 | t39);
    t41 = (~(t40));
    t42 = (t37 & t41);
    if (t42 != 0)
        goto LAB16;

LAB13:    if (t40 != 0)
        goto LAB15;

LAB14:    *((unsigned int *)t28) = 1;

LAB16:    t44 = (t28 + 4);
    t45 = *((unsigned int *)t44);
    t46 = (~(t45));
    t47 = *((unsigned int *)t28);
    t48 = (t47 & t46);
    t49 = (t48 != 0);
    if (t49 > 0)
        goto LAB17;

LAB18:
LAB19:    xsi_set_current_line(71, ng0);
    t2 = (t0 + 5928);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    memset(t6, 0, 8);
    xsi_vlog_signed_add(t6, 32, t4, 32, t5, 32);
    t7 = (t0 + 5928);
    xsi_vlogvar_assign_value(t7, t6, 0, 0, 32);
    goto LAB9;

LAB15:    t43 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t43) = 1;
    goto LAB16;

LAB17:    xsi_set_current_line(72, ng0);

LAB20:    xsi_set_current_line(73, ng0);
    t50 = (t0 + 5288);
    t51 = (t50 + 56U);
    t52 = *((char **)t51);
    t53 = ((char*)((ng5)));
    memset(t54, 0, 8);
    xsi_vlog_unsigned_add(t54, 32, t52, 8, t53, 32);
    t55 = (t0 + 5288);
    xsi_vlogvar_assign_value(t55, t54, 0, 0, 8);
    xsi_set_current_line(74, ng0);
    t2 = (t0 + 5608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    xsi_vlog_unsigned_lshift(t24, 48, t4, 48, t5, 32);
    t7 = (t0 + 5608);
    xsi_vlogvar_assign_value(t7, t24, 0, 0, 48);
    goto LAB19;

LAB23:    t15 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t15) = 1;
    goto LAB24;

LAB25:    xsi_set_current_line(86, ng0);

LAB28:    xsi_set_current_line(87, ng0);
    t17 = (t0 + 4968);
    t22 = (t17 + 56U);
    t25 = *((char **)t22);
    t27 = ((char*)((ng5)));
    memset(t23, 0, 8);
    xsi_vlog_unsigned_add(t23, 32, t25, 8, t27, 32);
    t29 = (t0 + 4968);
    xsi_vlogvar_assign_value(t29, t23, 0, 0, 8);
    goto LAB27;

}

static void Always_96_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;

LAB0:    t1 = (t0 + 7088U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(96, ng0);
    t2 = (t0 + 7424);
    *((int *)t2) = 1;
    t3 = (t0 + 7120);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(96, ng0);

LAB5:    xsi_set_current_line(98, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(102, ng0);

LAB10:    xsi_set_current_line(103, ng0);
    t2 = (t0 + 2408);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t5, t4, 0, 0, 32, 0LL);
    xsi_set_current_line(104, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 1, 0LL);

LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(98, ng0);

LAB9:    xsi_set_current_line(99, ng0);
    t11 = ((char*)((ng2)));
    t12 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 32, 0LL);
    xsi_set_current_line(100, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB8;

}


extern void work_m_16796821124068800998_1101851702_init()
{
	static char *pe[] = {(void *)Always_53_0,(void *)Always_96_1};
	xsi_register_didat("work_m_16796821124068800998_1101851702", "isim/SPFPMultiplier_tb_isim_beh.exe.sim/work/m_16796821124068800998_1101851702.didat");
	xsi_register_executes(pe);
}
