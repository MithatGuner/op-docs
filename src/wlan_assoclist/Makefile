#
#
# Copyright (C) 2019 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=wlan_assoclist
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/wlan_assoclist
  SECTION:=base
  CATEGORY:=gl-inet
  TITLE:=Wireless Client List for MTK
endef

define Package/wlan_assoclist/description
A Demo for Getting Wireless Client List from MTK Driver.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Build/Compile
	$(call Build/Compile/Default)
endef

define Package/wlan_assoclist/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/assoclist_demo $(1)/usr/bin
endef

$(eval $(call BuildPackage,wlan_assoclist))
