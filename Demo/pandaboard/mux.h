/*
 * (C) Copyright 2004-2009
 * Texas Instruments Incorporated
 * Richard Woodruff     <r-woodruff2@ti.com>
 * Aneesh V         <aneesh@ti.com>
 * Balaji Krishnamoorthy    <balajitk@ti.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */
#ifndef _MUX_OMAP4_H_
#define _MUX_OMAP4_H_

//#include <asm/types.h>

#include "FreeRTOS.h"

/*
 * Non-secure SRAM Addresses
 * Non-secure RAM starts at 0x40300000 for GP devices. But we keep SRAM_BASE
 * at 0x40304000(EMU base) so that our code works for both EMU and GP
 */
#define NON_SECURE_SRAM_START   0x40304000
#define NON_SECURE_SRAM_END 0x4030E000  /* Not inclusive */
#define SRAM_SCRATCH_SPACE_ADDR 0x4030C000
/* base address for indirect vectors (internal boot mode) */
#define SRAM_ROM_VECT_BASE  0x4030D000


#define OMAP_SRAM_SCRATCH_OMAP_REV  SRAM_SCRATCH_SPACE_ADDR
#define OMAP_SRAM_SCRATCH_EMIF_SIZE (SRAM_SCRATCH_SPACE_ADDR + 0x4)
#define OMAP_SRAM_SCRATCH_EMIF_T_NUM    (SRAM_SCRATCH_SPACE_ADDR + 0xC)
#define OMAP_SRAM_SCRATCH_EMIF_T_DEN    (SRAM_SCRATCH_SPACE_ADDR + 0x10)
#define OMAP_SRAM_SCRATCH_PRCM_PTR      (SRAM_SCRATCH_SPACE_ADDR + 0x14)
#define OMAP_SRAM_SCRATCH_DPLLS_PTR     (SRAM_SCRATCH_SPACE_ADDR + 0x18)
#define OMAP_SRAM_SCRATCH_VCORES_PTR    (SRAM_SCRATCH_SPACE_ADDR + 0x1C)
#define OMAP_SRAM_SCRATCH_SYS_CTRL  (SRAM_SCRATCH_SPACE_ADDR + 0x20)
#define OMAP_SRAM_SCRATCH_BOOT_PARAMS   (SRAM_SCRATCH_SPACE_ADDR + 0x24)
#define OMAP5_SRAM_SCRATCH_SPACE_END    (SRAM_SCRATCH_SPACE_ADDR + 0x28)


struct omap_sys_ctrl_regs {
    u32 control_status;
    u32 control_core_mac_id_0_lo;
    u32 control_core_mac_id_0_hi;
    u32 control_core_mac_id_1_lo;
    u32 control_core_mac_id_1_hi;
    u32 control_std_fuse_opp_vdd_mpu_2;
    u32 control_phy_power_usb;
    u32 control_core_mmr_lock1;
    u32 control_core_mmr_lock2;
    u32 control_core_mmr_lock3;
    u32 control_core_mmr_lock4;
    u32 control_core_mmr_lock5;
    u32 control_core_control_io1;
    u32 control_core_control_io2;
    u32 control_id_code;
    u32 control_std_fuse_die_id_0;
    u32 control_std_fuse_die_id_1;
    u32 control_std_fuse_die_id_2;
    u32 control_std_fuse_die_id_3;
    u32 control_std_fuse_opp_bgap;
    u32 control_ldosram_iva_voltage_ctrl;
    u32 control_ldosram_mpu_voltage_ctrl;
    u32 control_ldosram_core_voltage_ctrl;
    u32 control_usbotghs_ctrl;
    u32 control_phy_power_sata;
    u32 control_padconf_core_base;
    u32 control_paconf_global;
    u32 control_paconf_mode;
    u32 control_smart1io_padconf_0;
    u32 control_smart1io_padconf_1;
    u32 control_smart1io_padconf_2;
    u32 control_smart2io_padconf_0;
    u32 control_smart2io_padconf_1;
    u32 control_smart2io_padconf_2;
    u32 control_smart3io_padconf_0;
    u32 control_smart3io_padconf_1;
    u32 control_pbias;
    u32 control_i2c_0;
    u32 control_camera_rx;
    u32 control_hdmi_tx_phy;
    u32 control_uniportm;
    u32 control_dsiphy;
    u32 control_mcbsplp;
    u32 control_usb2phycore;
    u32 control_hdmi_1;
    u32 control_hsi;
    u32 control_ddr3ch1_0;
    u32 control_ddr3ch2_0;
    u32 control_ddrch1_0;
    u32 control_ddrch1_1;
    u32 control_ddrch2_0;
    u32 control_ddrch2_1;
    u32 control_lpddr2ch1_0;
    u32 control_lpddr2ch1_1;
    u32 control_ddrio_0;
    u32 control_ddrio_1;
    u32 control_ddrio_2;
    u32 control_ddr_control_ext_0;
    u32 control_lpddr2io1_0;
    u32 control_lpddr2io1_1;
    u32 control_lpddr2io1_2;
    u32 control_lpddr2io1_3;
    u32 control_lpddr2io2_0;
    u32 control_lpddr2io2_1;
    u32 control_lpddr2io2_2;
    u32 control_lpddr2io2_3;
    u32 control_hyst_1;
    u32 control_usbb_hsic_control;
    u32 control_c2c;
    u32 control_core_control_spare_rw;
    u32 control_core_control_spare_r;
    u32 control_core_control_spare_r_c0;
    u32 control_srcomp_north_side;
    u32 control_srcomp_south_side;
    u32 control_srcomp_east_side;
    u32 control_srcomp_west_side;
    u32 control_srcomp_code_latch;
    u32 control_pbiaslite;
    u32 control_port_emif1_sdram_config;
    u32 control_port_emif1_lpddr2_nvm_config;
    u32 control_port_emif2_sdram_config;
    u32 control_emif1_sdram_config_ext;
    u32 control_emif2_sdram_config_ext;
    u32 control_wkup_ldovbb_mpu_voltage_ctrl;
    u32 control_smart1nopmio_padconf_0;
    u32 control_smart1nopmio_padconf_1;
    u32 control_padconf_mode;
    u32 control_xtal_oscillator;
    u32 control_i2c_2;
    u32 control_ckobuffer;
    u32 control_wkup_control_spare_rw;
    u32 control_wkup_control_spare_r;
    u32 control_wkup_control_spare_r_c0;
    u32 control_srcomp_east_side_wkup;
    u32 control_efuse_1;
    u32 control_efuse_2;
    u32 control_efuse_3;
    u32 control_efuse_4;
    u32 control_efuse_5;
    u32 control_efuse_6;
    u32 control_efuse_7;
    u32 control_efuse_8;
    u32 control_efuse_9;
    u32 control_efuse_10;
    u32 control_efuse_11;
    u32 control_efuse_12;
    u32 control_efuse_13;
    u32 control_padconf_wkup_base;
    u32 iodelay_config_base;
    u32 ctrl_core_sma_sw_0;
    u32 ctrl_core_sma_sw_1;
};


struct pad_conf_entry {
    u16 offset;
    u16 val;
};

#ifdef CONFIG_OFF_PADCONF
#define OFF_PD          (1 << 12)
#define OFF_PU          (3 << 12)
#define OFF_OUT_PTD     (0 << 10)
#define OFF_OUT_PTU     (2 << 10)
#define OFF_IN          (1 << 10)
#define OFF_OUT         (0 << 10)
#define OFF_EN          (1 << 9)
#else
#define OFF_PD          (0 << 12)
#define OFF_PU          (0 << 12)
#define OFF_OUT_PTD     (0 << 10)
#define OFF_OUT_PTU     (0 << 10)
#define OFF_IN          (0 << 10)
#define OFF_OUT         (0 << 10)
#define OFF_EN          (0 << 9)
#endif

#define IEN             (1 << 8)
#define IDIS            (0 << 8)
#define PTU             (3 << 3)
#define PTD             (1 << 3)
#define EN              (1 << 3)
#define DIS             (0 << 3)

#define M0              0
#define M1              1
#define M2              2
#define M3              3
#define M4              4
#define M5              5
#define M6              6
#define M7              7

#define SAFE_MODE   M7

#ifdef CONFIG_OFF_PADCONF
#define OFF_IN_PD       (OFF_PD | OFF_IN | OFF_EN)
#define OFF_IN_PU       (OFF_PU | OFF_IN | OFF_EN)
#define OFF_OUT_PD      (OFF_OUT_PTD | OFF_OUT | OFF_EN)
#define OFF_OUT_PU      (OFF_OUT_PTU | OFF_OUT | OFF_EN)
#else
#define OFF_IN_PD       0
#define OFF_IN_PU       0
#define OFF_OUT_PD      0
#define OFF_OUT_PU      0
#endif

#define CORE_REVISION       0x0000
#define CORE_HWINFO     0x0004
#define CORE_SYSCONFIG      0x0010
#define GPMC_AD0        0x0040
#define GPMC_AD1        0x0042
#define GPMC_AD2        0x0044
#define GPMC_AD3        0x0046
#define GPMC_AD4        0x0048
#define GPMC_AD5        0x004A
#define GPMC_AD6        0x004C
#define GPMC_AD7        0x004E
#define GPMC_AD8        0x0050
#define GPMC_AD9        0x0052
#define GPMC_AD10       0x0054
#define GPMC_AD11       0x0056
#define GPMC_AD12       0x0058
#define GPMC_AD13       0x005A
#define GPMC_AD14       0x005C
#define GPMC_AD15       0x005E
#define GPMC_A16        0x0060
#define GPMC_A17        0x0062
#define GPMC_A18        0x0064
#define GPMC_A19        0x0066
#define GPMC_A20        0x0068
#define GPMC_A21        0x006A
#define GPMC_A22        0x006C
#define GPMC_A23        0x006E
#define GPMC_A24        0x0070
#define GPMC_A25        0x0072
#define GPMC_NCS0       0x0074
#define GPMC_NCS1       0x0076
#define GPMC_NCS2       0x0078
#define GPMC_NCS3       0x007A
#define GPMC_NWP        0x007C
#define GPMC_CLK        0x007E
#define GPMC_NADV_ALE       0x0080
#define GPMC_NOE        0x0082
#define GPMC_NWE        0x0084
#define GPMC_NBE0_CLE       0x0086
#define GPMC_NBE1       0x0088
#define GPMC_WAIT0      0x008A
#define GPMC_WAIT1      0x008C
#define C2C_DATA11      0x008E
#define C2C_DATA12      0x0090
#define C2C_DATA13      0x0092
#define C2C_DATA14      0x0094
#define C2C_DATA15      0x0096
#define HDMI_HPD        0x0098
#define HDMI_CEC        0x009A
#define HDMI_DDC_SCL        0x009C
#define HDMI_DDC_SDA        0x009E
#define CSI21_DX0       0x00A0
#define CSI21_DY0       0x00A2
#define CSI21_DX1       0x00A4
#define CSI21_DY1       0x00A6
#define CSI21_DX2       0x00A8
#define CSI21_DY2       0x00AA
#define CSI21_DX3       0x00AC
#define CSI21_DY3       0x00AE
#define CSI21_DX4       0x00B0
#define CSI21_DY4       0x00B2
#define CSI22_DX0       0x00B4
#define CSI22_DY0       0x00B6
#define CSI22_DX1       0x00B8
#define CSI22_DY1       0x00BA
#define CAM_SHUTTER     0x00BC
#define CAM_STROBE      0x00BE
#define CAM_GLOBALRESET     0x00C0
#define USBB1_ULPITLL_CLK   0x00C2
#define USBB1_ULPITLL_STP   0x00C4
#define USBB1_ULPITLL_DIR   0x00C6
#define USBB1_ULPITLL_NXT   0x00C8
#define USBB1_ULPITLL_DAT0  0x00CA
#define USBB1_ULPITLL_DAT1  0x00CC
#define USBB1_ULPITLL_DAT2  0x00CE
#define USBB1_ULPITLL_DAT3  0x00D0
#define USBB1_ULPITLL_DAT4  0x00D2
#define USBB1_ULPITLL_DAT5  0x00D4
#define USBB1_ULPITLL_DAT6  0x00D6
#define USBB1_ULPITLL_DAT7  0x00D8
#define USBB1_HSIC_DATA     0x00DA
#define USBB1_HSIC_STROBE   0x00DC
#define USBC1_ICUSB_DP      0x00DE
#define USBC1_ICUSB_DM      0x00E0
#define SDMMC1_CLK      0x00E2
#define SDMMC1_CMD      0x00E4
#define SDMMC1_DAT0     0x00E6
#define SDMMC1_DAT1     0x00E8
#define SDMMC1_DAT2     0x00EA
#define SDMMC1_DAT3     0x00EC
#define SDMMC1_DAT4     0x00EE
#define SDMMC1_DAT5     0x00F0
#define SDMMC1_DAT6     0x00F2
#define SDMMC1_DAT7     0x00F4
#define ABE_MCBSP2_CLKX     0x00F6
#define ABE_MCBSP2_DR       0x00F8
#define ABE_MCBSP2_DX       0x00FA
#define ABE_MCBSP2_FSX      0x00FC
#define ABE_MCBSP1_CLKX     0x00FE
#define ABE_MCBSP1_DR       0x0100
#define ABE_MCBSP1_DX       0x0102
#define ABE_MCBSP1_FSX      0x0104
#define ABE_PDM_UL_DATA     0x0106
#define ABE_PDM_DL_DATA     0x0108
#define ABE_PDM_FRAME       0x010A
#define ABE_PDM_LB_CLK      0x010C
#define ABE_CLKS        0x010E
#define ABE_DMIC_CLK1       0x0110
#define ABE_DMIC_DIN1       0x0112
#define ABE_DMIC_DIN2       0x0114
#define ABE_DMIC_DIN3       0x0116
#define UART2_CTS       0x0118
#define UART2_RTS       0x011A
#define UART2_RX        0x011C
#define UART2_TX        0x011E
#define HDQ_SIO         0x0120
#define I2C1_SCL        0x0122
#define I2C1_SDA        0x0124
#define I2C2_SCL        0x0126
#define I2C2_SDA        0x0128
#define I2C3_SCL        0x012A
#define I2C3_SDA        0x012C
#define I2C4_SCL        0x012E
#define I2C4_SDA        0x0130
#define MCSPI1_CLK      0x0132
#define MCSPI1_SOMI     0x0134
#define MCSPI1_SIMO     0x0136
#define MCSPI1_CS0      0x0138
#define MCSPI1_CS1      0x013A
#define MCSPI1_CS2      0x013C
#define MCSPI1_CS3      0x013E
#define UART3_CTS_RCTX      0x0140
#define UART3_RTS_SD        0x0142
#define UART3_RX_IRRX       0x0144
#define UART3_TX_IRTX       0x0146
#define SDMMC5_CLK      0x0148
#define SDMMC5_CMD      0x014A
#define SDMMC5_DAT0     0x014C
#define SDMMC5_DAT1     0x014E
#define SDMMC5_DAT2     0x0150
#define SDMMC5_DAT3     0x0152
#define MCSPI4_CLK      0x0154
#define MCSPI4_SIMO     0x0156
#define MCSPI4_SOMI     0x0158
#define MCSPI4_CS0      0x015A
#define UART4_RX        0x015C
#define UART4_TX        0x015E
#define USBB2_ULPITLL_CLK   0x0160
#define USBB2_ULPITLL_STP   0x0162
#define USBB2_ULPITLL_DIR   0x0164
#define USBB2_ULPITLL_NXT   0x0166
#define USBB2_ULPITLL_DAT0  0x0168
#define USBB2_ULPITLL_DAT1  0x016A
#define USBB2_ULPITLL_DAT2  0x016C
#define USBB2_ULPITLL_DAT3  0x016E
#define USBB2_ULPITLL_DAT4  0x0170
#define USBB2_ULPITLL_DAT5  0x0172
#define USBB2_ULPITLL_DAT6  0x0174
#define USBB2_ULPITLL_DAT7  0x0176
#define USBB2_HSIC_DATA     0x0178
#define USBB2_HSIC_STROBE   0x017A
#define UNIPRO_TX0      0x017C
#define UNIPRO_TY0      0x017E
#define UNIPRO_TX1      0x0180
#define UNIPRO_TY1      0x0182
#define UNIPRO_TX2      0x0184
#define UNIPRO_TY2      0x0186
#define UNIPRO_RX0      0x0188
#define UNIPRO_RY0      0x018A
#define UNIPRO_RX1      0x018C
#define UNIPRO_RY1      0x018E
#define UNIPRO_RX2      0x0190
#define UNIPRO_RY2      0x0192
#define USBA0_OTG_CE        0x0194
#define USBA0_OTG_DP        0x0196
#define USBA0_OTG_DM        0x0198
#define FREF_CLK1_OUT       0x019A
#define FREF_CLK2_OUT       0x019C
#define SYS_NIRQ1       0x019E
#define SYS_NIRQ2       0x01A0
#define SYS_BOOT0       0x01A2
#define SYS_BOOT1       0x01A4
#define SYS_BOOT2       0x01A6
#define SYS_BOOT3       0x01A8
#define SYS_BOOT4       0x01AA
#define SYS_BOOT5       0x01AC
#define DPM_EMU0        0x01AE
#define DPM_EMU1        0x01B0
#define DPM_EMU2        0x01B2
#define DPM_EMU3        0x01B4
#define DPM_EMU4        0x01B6
#define DPM_EMU5        0x01B8
#define DPM_EMU6        0x01BA
#define DPM_EMU7        0x01BC
#define DPM_EMU8        0x01BE
#define DPM_EMU9        0x01C0
#define DPM_EMU10       0x01C2
#define DPM_EMU11       0x01C4
#define DPM_EMU12       0x01C6
#define DPM_EMU13       0x01C8
#define DPM_EMU14       0x01CA
#define DPM_EMU15       0x01CC
#define DPM_EMU16       0x01CE
#define DPM_EMU17       0x01D0
#define DPM_EMU18       0x01D2
#define DPM_EMU19       0x01D4
#define WAKEUPEVENT_0       0x01D8
#define WAKEUPEVENT_1       0x01DC
#define WAKEUPEVENT_2       0x01E0
#define WAKEUPEVENT_3       0x01E4
#define WAKEUPEVENT_4       0x01E8
#define WAKEUPEVENT_5       0x01EC
#define WAKEUPEVENT_6       0x01F0

#define WKUP_REVISION       0x0000
#define WKUP_HWINFO     0x0004
#define WKUP_SYSCONFIG      0x0010
#define PAD0_SIM_IO     0x0040
#define PAD1_SIM_CLK        0x0042
#define PAD0_SIM_RESET      0x0044
#define PAD1_SIM_CD     0x0046
#define PAD0_SIM_PWRCTRL        0x0048
#define PAD1_SR_SCL     0x004A
#define PAD0_SR_SDA     0x004C
#define PAD1_FREF_XTAL_IN       0x004E
#define PAD0_FREF_SLICER_IN 0x0050
#define PAD1_FREF_CLK_IOREQ 0x0052
#define PAD0_FREF_CLK0_OUT      0x0054
#define PAD1_FREF_CLK3_REQ      0x0056
#define PAD0_FREF_CLK3_OUT      0x0058
#define PAD1_FREF_CLK4_REQ      0x005A
#define PAD0_FREF_CLK4_OUT      0x005C
#define PAD1_SYS_32K        0x005E
#define PAD0_SYS_NRESPWRON      0x0060
#define PAD1_SYS_NRESWARM       0x0062
#define PAD0_SYS_PWR_REQ        0x0064
#define PAD1_SYS_PWRON_RESET    0x0066
#define PAD0_SYS_BOOT6      0x0068
#define PAD1_SYS_BOOT7      0x006A
#define PAD0_JTAG_NTRST     0x006C
#define PAD1_JTAG_TCK       0x006D
#define PAD0_JTAG_RTCK      0x0070
#define PAD1_JTAG_TMS_TMSC      0x0072
#define PAD0_JTAG_TDI       0x0074
#define PAD1_JTAG_TDO       0x0076
#define PADCONF_WAKEUPEVENT_0   0x007C
#define CONTROL_SMART1NOPMIO_PADCONF_0      0x05A0
#define CONTROL_SMART1NOPMIO_PADCONF_1      0x05A4
#define PADCONF_MODE        0x05A8
#define CONTROL_XTAL_OSCILLATOR         0x05AC
#define CONTROL_CONTROL_I2C_2           0x0604
#define CONTROL_CONTROL_JTAG            0x0608
#define CONTROL_CONTROL_SYS         0x060C
#define CONTROL_SPARE_RW        0x0614
#define CONTROL_SPARE_R     0x0618
#define CONTROL_SPARE_R_C0      0x061C

#define CONTROL_WKUP_PAD1_FREF_CLK4_REQ 0x4A31E05A



const struct pad_conf_entry core_padconf_array_non_essential[] = {
    {GPMC_AD8, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M3)},    /* gpio_32 */
    {GPMC_AD9, (PTU | IEN | M3)},                   /* gpio_33 */
    {GPMC_AD10, (PTU | IEN | M3)},                  /* gpio_34 */
    {GPMC_AD11, (PTU | IEN | M3)},                  /* gpio_35 */
    {GPMC_AD12, (PTU | IEN | M3)},                  /* gpio_36 */
    {GPMC_AD13, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3)},    /* gpio_37 */
    {GPMC_AD14, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3)},    /* gpio_38 */
    {GPMC_AD15, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3)},    /* gpio_39 */
    {GPMC_A16, (M3)},                       /* gpio_40 */
    {GPMC_A17, (PTD | M3)},                     /* gpio_41 */
    {GPMC_A18, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1)},    /* kpd_row6 */
    {GPMC_A19, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1)},    /* kpd_row7 */
    {GPMC_A20, (IEN | M3)},                     /* gpio_44 */
    {GPMC_A21, (M3)},                       /* gpio_45 */
    {GPMC_A22, (M3)},                       /* gpio_46 */
    {GPMC_A23, (OFF_EN | OFF_PD | OFF_IN | M1)},            /* kpd_col7 */
    {GPMC_A24, (PTD | M3)},                     /* gpio_48 */
    {GPMC_A25, (PTD | M3)},                     /* gpio_49 */
    {GPMC_NCS0, (M3)},                      /* gpio_50 */
    {GPMC_NCS1, (IEN | M3)},                    /* gpio_51 */
    {GPMC_NCS2, (IEN | M3)},                    /* gpio_52 */
    {GPMC_NCS3, (IEN | M3)},                    /* gpio_53 */
    {GPMC_NWP, (M3)},                       /* gpio_54 */
    {GPMC_CLK, (PTD | M3)},                     /* gpio_55 */
    {GPMC_NADV_ALE, (M3)},                      /* gpio_56 */
    {GPMC_NBE0_CLE, (M3)},                      /* gpio_59 */
    {GPMC_NBE1, (PTD | M3)},                    /* gpio_60 */
    {GPMC_WAIT0, (PTU | IEN | M3)},                 /* gpio_61 */
    {GPMC_WAIT1,  (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3)},  /* gpio_62 */
    {C2C_DATA11, (PTD | M3)},                   /* gpio_100 */
    {C2C_DATA12, (PTU | IEN | M3)},                 /* gpio_101 */
    {C2C_DATA13, (PTD | M3)},                   /* gpio_102 */
    {C2C_DATA14, (M1)},                     /* dsi2_te0 */
    {C2C_DATA15, (PTD | M3)},                   /* gpio_104 */
    {HDMI_HPD, (M0)},                       /* hdmi_hpd */
    {HDMI_CEC, (M0)},                       /* hdmi_cec */
    {HDMI_DDC_SCL, (PTU | M0)},                 /* hdmi_ddc_scl */
    {HDMI_DDC_SDA, (PTU | IEN | M0)},               /* hdmi_ddc_sda */
    {CSI21_DX0, (IEN | M0)},                    /* csi21_dx0 */
    {CSI21_DY0, (IEN | M0)},                    /* csi21_dy0 */
    {CSI21_DX1, (IEN | M0)},                    /* csi21_dx1 */
    {CSI21_DY1, (IEN | M0)},                    /* csi21_dy1 */
    {CSI21_DX2, (IEN | M0)},                    /* csi21_dx2 */
    {CSI21_DY2, (IEN | M0)},                    /* csi21_dy2 */
    {CSI21_DX3, (PTD | M7)},                    /* csi21_dx3 */
    {CSI21_DY3, (PTD | M7)},                    /* csi21_dy3 */
    {CSI21_DX4, (PTD | OFF_EN | OFF_PD | OFF_IN | M7)},     /* csi21_dx4 */
    {CSI21_DY4, (PTD | OFF_EN | OFF_PD | OFF_IN | M7)},     /* csi21_dy4 */
    {CSI22_DX0, (IEN | M0)},                    /* csi22_dx0 */
    {CSI22_DY0, (IEN | M0)},                    /* csi22_dy0 */
    {CSI22_DX1, (IEN | M0)},                    /* csi22_dx1 */
    {CSI22_DY1, (IEN | M0)},                    /* csi22_dy1 */
    {CAM_SHUTTER, (OFF_EN | OFF_PD | OFF_OUT_PTD | M0)},        /* cam_shutter */
    {CAM_STROBE, (OFF_EN | OFF_PD | OFF_OUT_PTD | M0)},     /* cam_strobe */
    {CAM_GLOBALRESET, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3)},  /* gpio_83 */
    {USBB1_ULPITLL_CLK, (IEN | OFF_EN | OFF_IN | M1)},      /* hsi1_cawake */
    {USBB1_ULPITLL_STP, (IEN | OFF_EN | OFF_IN | M1)},      /* hsi1_cadata */
    {USBB1_ULPITLL_DIR, (IEN | OFF_EN | OFF_IN | M1)},      /* hsi1_caflag */
    {USBB1_ULPITLL_NXT, (OFF_EN | M1)},             /* hsi1_acready */
    {USBB1_ULPITLL_DAT0, (OFF_EN | M1)},                /* hsi1_acwake */
    {USBB1_ULPITLL_DAT1, (OFF_EN | M1)},                /* hsi1_acdata */
    {USBB1_ULPITLL_DAT2, (OFF_EN | M1)},                /* hsi1_acflag */
    {USBB1_ULPITLL_DAT3, (IEN | OFF_EN | OFF_IN | M1)},     /* hsi1_caready */
    {USBB1_ULPITLL_DAT4, (IEN | OFF_EN | OFF_PD | OFF_IN | M4)},    /* usbb1_ulpiphy_dat4 */
    {USBB1_ULPITLL_DAT5, (IEN | OFF_EN | OFF_PD | OFF_IN | M4)},    /* usbb1_ulpiphy_dat5 */
    {USBB1_ULPITLL_DAT6, (IEN | OFF_EN | OFF_PD | OFF_IN | M4)},    /* usbb1_ulpiphy_dat6 */
    {USBB1_ULPITLL_DAT7, (IEN | OFF_EN | OFF_PD | OFF_IN | M4)},    /* usbb1_ulpiphy_dat7 */
    {USBB1_HSIC_DATA, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},   /* usbb1_hsic_data */
    {USBB1_HSIC_STROBE, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)}, /* usbb1_hsic_strobe */
    {USBC1_ICUSB_DP, (IEN | M0)},                   /* usbc1_icusb_dp */
    {USBC1_ICUSB_DM, (IEN | M0)},                   /* usbc1_icusb_dm */
    {ABE_MCBSP2_DR, (IEN | OFF_EN | OFF_OUT_PTD | M0)},     /* abe_mcbsp2_dr */
    {ABE_MCBSP2_DX, (OFF_EN | OFF_OUT_PTD | M0)},           /* abe_mcbsp2_dx */
//    {ABE_MCBSP2_FSX, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},    /* abe_mcbsp2_fsx */
    {ABE_MCBSP2_FSX, (PTU | IEN | M3)},                   /* gpio_113 */
    {ABE_MCBSP1_CLKX, (IEN | M0)},                  /* abe_mcbsp1_clkx */
    {ABE_MCBSP1_DR, (IEN | M0)},                    /* abe_mcbsp1_dr */
    {ABE_MCBSP1_DX, (OFF_EN | OFF_OUT_PTD | M0)},           /* abe_mcbsp1_dx */
    {ABE_MCBSP1_FSX, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},    /* abe_mcbsp1_fsx */
    {ABE_PDM_UL_DATA, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0)}, /* abe_pdm_ul_data */
    {ABE_PDM_DL_DATA, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0)}, /* abe_pdm_dl_data */
    {ABE_PDM_FRAME, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0)},   /* abe_pdm_frame */
    {ABE_PDM_LB_CLK, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0)},  /* abe_pdm_lb_clk */
    {ABE_CLKS, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0)},    /* abe_clks */
    {ABE_DMIC_CLK1, (M0)},                      /* abe_dmic_clk1 */
    {ABE_DMIC_DIN1, (IEN | M0)},                    /* abe_dmic_din1 */
    {ABE_DMIC_DIN2, (PTU | IEN | M3)},              /* gpio_121 */
    {ABE_DMIC_DIN3, (IEN | M0)},                    /* abe_dmic_din3 */
    {UART2_CTS, (PTU | IEN | M0)},                  /* uart2_cts */
    {UART2_RTS, (M0)},                      /* uart2_rts */
    {UART2_RX, (PTU | IEN | M0)},                   /* uart2_rx */
    {UART2_TX, (M0)},                       /* uart2_tx */
    {HDQ_SIO, (M3)},                        /* gpio_127 */
    {MCSPI1_CLK, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},        /* mcspi1_clk */
    {MCSPI1_SOMI, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},       /* mcspi1_somi */
    {MCSPI1_SIMO, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},       /* mcspi1_simo */
    {MCSPI1_CS0, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0)},  /* mcspi1_cs0 */
    {MCSPI1_CS1, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M3)},  /* mcspi1_cs1 */
    {MCSPI1_CS2, (PTU | OFF_EN | OFF_OUT_PTU | M3)},        /* gpio_139 */
    {MCSPI1_CS3, (PTU | IEN | M3)},                 /* gpio_140 */
    {SDMMC5_CLK, (PTU | IEN | OFF_EN | OFF_OUT_PTD | M0)},      /* sdmmc5_clk */
    {SDMMC5_CMD, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0)},  /* sdmmc5_cmd */
    {SDMMC5_DAT0, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0)}, /* sdmmc5_dat0 */
    {SDMMC5_DAT1, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0)}, /* sdmmc5_dat1 */
    {SDMMC5_DAT2, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0)}, /* sdmmc5_dat2 */
    {SDMMC5_DAT3, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0)}, /* sdmmc5_dat3 */
    {MCSPI4_CLK, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},        /* mcspi4_clk */
    {MCSPI4_SIMO, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},       /* mcspi4_simo */
    {MCSPI4_SOMI, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},       /* mcspi4_somi */
    {MCSPI4_CS0, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0)},  /* mcspi4_cs0 */
    {UART4_RX, (IEN | M0)},                     /* uart4_rx */
    {UART4_TX, (M0)},                       /* uart4_tx */
    {USBB2_ULPITLL_CLK, (IEN | M3)},                /* gpio_157 */
    {USBB2_ULPITLL_STP, (IEN | M5)},                /* dispc2_data23 */
    {USBB2_ULPITLL_DIR, (IEN | M5)},                /* dispc2_data22 */
    {USBB2_ULPITLL_NXT, (IEN | M5)},                /* dispc2_data21 */
    {USBB2_ULPITLL_DAT0, (IEN | M5)},               /* dispc2_data20 */
    {USBB2_ULPITLL_DAT1, (IEN | M5)},               /* dispc2_data19 */
    {USBB2_ULPITLL_DAT2, (IEN | M5)},               /* dispc2_data18 */
    {USBB2_ULPITLL_DAT3, (IEN | M5)},               /* dispc2_data15 */
    {USBB2_ULPITLL_DAT4, (IEN | M5)},               /* dispc2_data14 */
    {USBB2_ULPITLL_DAT5, (IEN | M5)},               /* dispc2_data13 */
    {USBB2_ULPITLL_DAT6, (IEN | M5)},               /* dispc2_data12 */
    {USBB2_ULPITLL_DAT7, (IEN | M5)},               /* dispc2_data11 */
    {USBB2_HSIC_DATA, (PTD | OFF_EN | OFF_OUT_PTU | M3)},       /* gpio_169 */
    {USBB2_HSIC_STROBE, (PTD | OFF_EN | OFF_OUT_PTU | M3)},     /* gpio_170 */
    {UNIPRO_TX0, (PTD | IEN | M3)},                 /* gpio_171 */
    {UNIPRO_TY0, (OFF_EN | OFF_PD | OFF_IN | M1)},          /* kpd_col1 */
    {UNIPRO_TX1, (OFF_EN | OFF_PD | OFF_IN | M1)},          /* kpd_col2 */
    {UNIPRO_TY1, (OFF_EN | OFF_PD | OFF_IN | M1)},          /* kpd_col3 */
    {UNIPRO_TX2, (PTU | IEN | M3)},                 /* gpio_0 */
    {UNIPRO_TY2, (PTU | IEN | M3)},                 /* gpio_1 */
    {UNIPRO_RX0, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1)},  /* kpd_row0 */
    {UNIPRO_RY0, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1)},  /* kpd_row1 */
    {UNIPRO_RX1, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1)},  /* kpd_row2 */
    {UNIPRO_RY1, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1)},  /* kpd_row3 */
    {UNIPRO_RX2, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1)},  /* kpd_row4 */
    {UNIPRO_RY2, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1)},  /* kpd_row5 */
    {USBA0_OTG_CE, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M0)}, /* usba0_otg_ce */
    {USBA0_OTG_DP, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},      /* usba0_otg_dp */
    {USBA0_OTG_DM, (IEN | OFF_EN | OFF_PD | OFF_IN | M0)},      /* usba0_otg_dm */
    {FREF_CLK1_OUT, (M0)},                      /* fref_clk1_out */
    {FREF_CLK2_OUT, (PTU | IEN | M3)},              /* gpio_182 */
    {SYS_NIRQ1, (PTU | IEN | M0)},                  /* sys_nirq1 */
    {SYS_NIRQ2, (PTU | IEN | M0)},                  /* sys_nirq2 */
    {SYS_BOOT0, (PTU | IEN | M3)},                  /* gpio_184 */
    {SYS_BOOT1, (M3)},                      /* gpio_185 */
    {SYS_BOOT2, (PTD | IEN | M3)},                  /* gpio_186 */
    {SYS_BOOT3, (M3)},                      /* gpio_187 */
    {SYS_BOOT4, (M3)},                      /* gpio_188 */
    {SYS_BOOT5, (PTD | IEN | M3)},                  /* gpio_189 */
    {DPM_EMU0, (IEN | M0)},                     /* dpm_emu0 */
    {DPM_EMU1, (IEN | M0)},                     /* dpm_emu1 */
    {DPM_EMU2, (IEN | M0)},                     /* dpm_emu2 */
    {DPM_EMU3, (IEN | M5)},                     /* dispc2_data10 */
    {DPM_EMU4, (IEN | M5)},                     /* dispc2_data9 */
    {DPM_EMU5, (IEN | M5)},                     /* dispc2_data16 */
    {DPM_EMU6, (IEN | M5)},                     /* dispc2_data17 */
    {DPM_EMU7, (IEN | M5)},                     /* dispc2_hsync */
    {DPM_EMU8, (IEN | M5)},                     /* dispc2_pclk */
    {DPM_EMU9, (IEN | M5)},                     /* dispc2_vsync */
    {DPM_EMU10, (IEN | M5)},                    /* dispc2_de */
    {DPM_EMU11, (IEN | M5)},                    /* dispc2_data8 */
    {DPM_EMU12, (IEN | M5)},                    /* dispc2_data7 */
    {DPM_EMU13, (IEN | M5)},                    /* dispc2_data6 */
    {DPM_EMU14, (IEN | M5)},                    /* dispc2_data5 */
    {DPM_EMU15, (IEN | M5)},                    /* dispc2_data4 */
    {DPM_EMU16, (M3)},                      /* gpio_27 */
    {DPM_EMU17, (IEN | M5)},                    /* dispc2_data2 */
    {DPM_EMU18, (IEN | M5)},                    /* dispc2_data1 */
    {DPM_EMU19, (IEN | M5)},                    /* dispc2_data0 */
};


const struct pad_conf_entry core_padconf_array_non_essential_4460[] = {
    {ABE_MCBSP2_CLKX, (PTU | OFF_EN | OFF_OUT_PTU | M3)},       /* led status_1 */
};

const struct pad_conf_entry wkup_padconf_array_non_essential[] = {
    {PAD0_SIM_IO, (IEN | M0)},      /* sim_io */
    {PAD1_SIM_CLK, (M0)},           /* sim_clk */
    {PAD0_SIM_RESET, (M0)},         /* sim_reset */
    {PAD1_SIM_CD, (PTU | IEN | M0)},    /* sim_cd */
    {PAD0_SIM_PWRCTRL, (M0)},       /* sim_pwrctrl */
    {PAD1_FREF_XTAL_IN, (M0)},      /* # */
    {PAD0_FREF_SLICER_IN, (M0)},        /* fref_slicer_in */
    {PAD1_FREF_CLK_IOREQ, (M0)},        /* fref_clk_ioreq */
    {PAD0_FREF_CLK0_OUT, (M2)},     /* sys_drm_msecure */
    {PAD1_FREF_CLK3_REQ, M7},       /* safe mode */
    {PAD0_FREF_CLK3_OUT, (M0)},     /* fref_clk3_out */
    {PAD0_FREF_CLK4_OUT, (PTU | M3)},   /* led status_2 */
    {PAD0_SYS_NRESPWRON, (M0)},     /* sys_nrespwron */
    {PAD1_SYS_NRESWARM, (M0)},      /* sys_nreswarm */
    {PAD0_SYS_PWR_REQ, (PTU | M0)},     /* sys_pwr_req */
    {PAD1_SYS_PWRON_RESET, (M3)},       /* gpio_wk29 */
    {PAD0_SYS_BOOT6, (IEN | M3)},       /* gpio_wk9 */
    {PAD1_SYS_BOOT7, (IEN | M3)},       /* gpio_wk10 */
};

#define GIC_DIST_OFFSET     0x1000
#define GIC_CPU_OFFSET_A9   0x0100
#define GIC_CPU_OFFSET_A15  0x2000

/* Distributor Registers */
#define GICD_CTLR       0x0000
#define GICD_TYPER      0x0004
#define GICD_IIDR       0x0008
#define GICD_STATUSR        0x0010
#define GICD_SETSPI_NSR     0x0040
#define GICD_CLRSPI_NSR     0x0048
#define GICD_SETSPI_SR      0x0050
#define GICD_CLRSPI_SR      0x0058
#define GICD_SEIR       0x0068
#define GICD_IGROUPRn       0x0080
#define GICD_ISENABLERn     0x0100
#define GICD_ICENABLERn     0x0180
#define GICD_ISPENDRn       0x0200
#define GICD_ICPENDRn       0x0280
#define GICD_ISACTIVERn     0x0300
#define GICD_ICACTIVERn     0x0380
#define GICD_IPRIORITYRn    0x0400
#define GICD_ITARGETSRn     0x0800
#define GICD_ICFGR      0x0c00
#define GICD_IGROUPMODRn    0x0d00
#define GICD_NSACRn     0x0e00
#define GICD_SGIR       0x0f00
#define GICD_CPENDSGIRn     0x0f10
#define GICD_SPENDSGIRn     0x0f20
#define GICD_IROUTERn       0x6000

/* Cpu Interface Memory Mapped Registers */
#define GICC_CTLR       0x0000
#define GICC_PMR        0x0004
#define GICC_BPR        0x0008
#define GICC_IAR        0x000C
#define GICC_EOIR       0x0010
#define GICC_RPR        0x0014
#define GICC_HPPIR      0x0018
#define GICC_ABPR       0x001c
#define GICC_AIAR       0x0020
#define GICC_AEOIR      0x0024
#define GICC_AHPPIR     0x0028
#define GICC_APRn       0x00d0
#define GICC_NSAPRn     0x00e0
#define GICC_IIDR       0x00fc
#define GICC_DIR        0x1000

/* ReDistributor Registers for Control and Physical LPIs */
#define GICR_CTLR       0x0000
#define GICR_IIDR       0x0004
#define GICR_TYPER      0x0008
#define GICR_STATUSR        0x0010
#define GICR_WAKER      0x0014
#define GICR_SETLPIR        0x0040
#define GICR_CLRLPIR        0x0048
#define GICR_SEIR       0x0068
#define GICR_PROPBASER      0x0070
#define GICR_PENDBASER      0x0078
#define GICR_INVLPIR        0x00a0
#define GICR_INVALLR        0x00b0
#define GICR_SYNCR      0x00c0
#define GICR_MOVLPIR        0x0100
#define GICR_MOVALLR        0x0110

/* ReDistributor Registers for SGIs and PPIs */
#define GICR_IGROUPRn       0x0080
#define GICR_ISENABLERn     0x0100
#define GICR_ICENABLERn     0x0180
#define GICR_ISPENDRn       0x0200
#define GICR_ICPENDRn       0x0280
#define GICR_ISACTIVERn     0x0300
#define GICR_ICACTIVERn     0x0380
#define GICR_IPRIORITYRn    0x0400
#define GICR_ICFGR0     0x0c00
#define GICR_ICFGR1     0x0c04
#define GICR_IGROUPMODRn    0x0d00
#define GICR_NSACRn     0x0e00

/* Cpu Interface System Registers */
#define ICC_IAR0_EL1        S3_0_C12_C8_0
#define ICC_IAR1_EL1        S3_0_C12_C12_0
#define ICC_EOIR0_EL1       S3_0_C12_C8_1
#define ICC_EOIR1_EL1       S3_0_C12_C12_1
#define ICC_HPPIR0_EL1      S3_0_C12_C8_2
#define ICC_HPPIR1_EL1      S3_0_C12_C12_2
#define ICC_BPR0_EL1        S3_0_C12_C8_3
#define ICC_BPR1_EL1        S3_0_C12_C12_3
#define ICC_DIR_EL1     S3_0_C12_C11_1
#define ICC_PMR_EL1     S3_0_C4_C6_0
#define ICC_RPR_EL1     S3_0_C12_C11_3
#define ICC_CTLR_EL1        S3_0_C12_C12_4
#define ICC_CTLR_EL3        S3_6_C12_C12_4
#define ICC_SRE_EL1     S3_0_C12_C12_5
#define ICC_SRE_EL2     S3_4_C12_C9_5
#define ICC_SRE_EL3     S3_6_C12_C12_5
#define ICC_IGRPEN0_EL1     S3_0_C12_C12_6
#define ICC_IGRPEN1_EL1     S3_0_C12_C12_7
#define ICC_IGRPEN1_EL3     S3_6_C12_C12_7
#define ICC_SEIEN_EL1       S3_0_C12_C13_0
#define ICC_SGI0R_EL1       S3_0_C12_C11_7
#define ICC_SGI1R_EL1       S3_0_C12_C11_5
#define ICC_ASGI1R_EL1      S3_0_C12_C11_6





#endif /* _MUX_OMAP4_H_ */
