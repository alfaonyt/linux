// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2024 alfaonyt <alfaonyt@gmail.com>
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved.

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <video/mipi_display.h>

#include <drm/display/drm_dsc.h>
#include <drm/display/drm_dsc_helper.h>
#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct m2a_42_02_0b_dsc {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct drm_dsc_config dsc;
	struct gpio_desc *reset_gpio;
};

static inline
struct m2a_42_02_0b_dsc *to_m2a_42_02_0b_dsc(struct drm_panel *panel)
{
	return container_of(panel, struct m2a_42_02_0b_dsc, panel);
}

static void m2a_42_02_0b_dsc_reset(struct m2a_42_02_0b_dsc *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int m2a_42_02_0b_dsc_on(struct m2a_42_02_0b_dsc *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x6f, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xc5, 0x0b, 0x0b, 0x0b);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0xaa, 0x55, 0xa5, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0x6f, 0x1b);
	mipi_dsi_dcs_write_seq(dsi, 0xf4, 0x55);
	mipi_dsi_dcs_write_seq(dsi, 0x90, 0x03, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x91,
			       0x89, 0x28, 0x00, 0x28, 0xd2, 0x00, 0x02, 0x86,
			       0x04, 0x3a, 0x00, 0x0a, 0x02, 0xab, 0x01, 0xe9,
			       0x10, 0xf0);

	ret = mipi_dsi_dcs_set_column_address(dsi, 0x0000, 0x059f);
	if (ret < 0) {
		dev_err(dev, "Failed to set column address: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_dcs_set_page_address(dsi, 0x0000, 0x0c7f);
	if (ret < 0) {
		dev_err(dev, "Failed to set page address: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	if (ret < 0) {
		dev_err(dev, "Failed to set tear on: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0x3b, 0x00, 0x18, 0x00, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0x5a, 0x01);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x9c, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x5f, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x5a, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x6f, 0x1c);
	mipi_dsi_dcs_write_seq(dsi, 0xba,
			       0x91, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xba, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x2f, 0x30);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x07);
	mipi_dsi_dcs_write_seq(dsi, 0xc0, 0xb0);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xbe, 0x47, 0xcf, 0x4c, 0x4b);
	mipi_dsi_dcs_write_seq(dsi, 0x6f, 0x09);
	mipi_dsi_dcs_write_seq(dsi, 0xbe, 0x2a);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xd1, 0x07, 0x02, 0x0c, 0x00, 0x00, 0x0f);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	mipi_dsi_dcs_write_seq(dsi, 0x9b, 0x00);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}

	return 0;
}

static int m2a_42_02_0b_dsc_off(struct m2a_42_02_0b_dsc *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	return 0;
}

static int m2a_42_02_0b_dsc_prepare(struct drm_panel *panel)
{
	struct m2a_42_02_0b_dsc *ctx = to_m2a_42_02_0b_dsc(panel);
	struct device *dev = &ctx->dsi->dev;
	struct drm_dsc_picture_parameter_set pps;
	int ret;

	m2a_42_02_0b_dsc_reset(ctx);

	ret = m2a_42_02_0b_dsc_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	drm_dsc_pps_payload_pack(&pps, &ctx->dsc);

	ret = mipi_dsi_picture_parameter_set(ctx->dsi, &pps);
	if (ret < 0) {
		dev_err(panel->dev, "failed to transmit PPS: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_compression_mode(ctx->dsi, true);
	if (ret < 0) {
		dev_err(dev, "failed to enable compression mode: %d\n", ret);
		return ret;
	}

	msleep(28); /* TODO: Is this panel-dependent? */

	return 0;
}

static int m2a_42_02_0b_dsc_unprepare(struct drm_panel *panel)
{
	struct m2a_42_02_0b_dsc *ctx = to_m2a_42_02_0b_dsc(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = m2a_42_02_0b_dsc_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode m2a_42_02_0b_dsc_mode = {
	.clock = (1440 + 20 + 8 + 20) * (3200 + 16 + 4 + 24) * 60 / 1000,
	.hdisplay = 1440,
	.hsync_start = 1440 + 20,
	.hsync_end = 1440 + 20 + 8,
	.htotal = 1440 + 20 + 8 + 20,
	.vdisplay = 3200,
	.vsync_start = 3200 + 16,
	.vsync_end = 3200 + 16 + 4,
	.vtotal = 3200 + 16 + 4 + 24,
	.width_mm = 701,
	.height_mm = 1558,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int m2a_42_02_0b_dsc_get_modes(struct drm_panel *panel,
				      struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &m2a_42_02_0b_dsc_mode);
}

static const struct drm_panel_funcs m2a_42_02_0b_dsc_panel_funcs = {
	.prepare = m2a_42_02_0b_dsc_prepare,
	.unprepare = m2a_42_02_0b_dsc_unprepare,
	.get_modes = m2a_42_02_0b_dsc_get_modes,
};

static int m2a_42_02_0b_dsc_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness = backlight_get_brightness(bl);
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness_large(dsi, brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return 0;
}

// TODO: Check if /sys/class/backlight/.../actual_brightness actually returns
// correct values. If not, remove this function.
static int m2a_42_02_0b_dsc_bl_get_brightness(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness_large(dsi, &brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return brightness;
}

static const struct backlight_ops m2a_42_02_0b_dsc_bl_ops = {
	.update_status = m2a_42_02_0b_dsc_bl_update_status,
	.get_brightness = m2a_42_02_0b_dsc_bl_get_brightness,
};

static struct backlight_device *
m2a_42_02_0b_dsc_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 2047,
		.max_brightness = 2047,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &m2a_42_02_0b_dsc_bl_ops, &props);
}

static int m2a_42_02_0b_dsc_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct m2a_42_02_0b_dsc *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &m2a_42_02_0b_dsc_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = m2a_42_02_0b_dsc_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	/* This panel only supports DSC; unconditionally enable it */
	dsi->dsc = &ctx->dsc;

	ctx->dsc.dsc_version_major = 1;
	ctx->dsc.dsc_version_minor = 1;

	/* TODO: Pass slice_per_pkt = 2 */
	ctx->dsc.slice_height = 40;
	ctx->dsc.slice_width = 720;
	/*
	 * TODO: hdisplay should be read from the selected mode once
	 * it is passed back to drm_panel (in prepare?)
	 */
	WARN_ON(1440 % ctx->dsc.slice_width);
	ctx->dsc.slice_count = 1440 / ctx->dsc.slice_width;
	ctx->dsc.bits_per_component = 8;
	ctx->dsc.bits_per_pixel = 8 << 4; /* 4 fractional bits */
	ctx->dsc.block_pred_enable = true;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void m2a_42_02_0b_dsc_remove(struct mipi_dsi_device *dsi)
{
	struct m2a_42_02_0b_dsc *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id m2a_42_02_0b_dsc_of_match[] = {
	{ .compatible = "tcl,m2a-dsc" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, m2a_42_02_0b_dsc_of_match);

static struct mipi_dsi_driver m2a_42_02_0b_dsc_driver = {
	.probe = m2a_42_02_0b_dsc_probe,
	.remove = m2a_42_02_0b_dsc_remove,
	.driver = {
		.name = "panel-m2a-42-02-0b-dsc",
		.of_match_table = m2a_42_02_0b_dsc_of_match,
	},
};
module_mipi_dsi_driver(m2a_42_02_0b_dsc_driver);

MODULE_AUTHOR("alfaonyt <alfaonyt@gmail.com>");
MODULE_DESCRIPTION("DRM driver for TCL M2A DSC command mode DSI panel");
MODULE_LICENSE("GPL");
