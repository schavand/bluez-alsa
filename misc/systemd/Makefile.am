# BlueALSA - Makefile.am
# Copyright (c) 2016-2021 Arkadiusz Bokowy

systemdbluealsaargs = $(SYSTEMD_BLUEALSA_ARGS)
systemdbluealsaaplayargs = $(SYSTEMD_BLUEALSA_APLAY_ARGS)

systemdsystemunitdir = $(SYSTEMD_SYSTEM_UNIT_DIR)

dist_systemdsystemunit_DATA = \
	bluealsa-aplay.service \
	bluealsa.service

SUFFIXES = .in
MOSTLYCLEANFILES = $(dist_systemdsystemunit_DATA)

SYSTEMD_SERVICE_SUBS = \
	s,[@]bindir[@],$(bindir),g; \
	s,[@]systemdbluealsaargs[@],$(systemdbluealsaargs),g; \
	s,[@]systemdbluealsaaplayargs[@],$(systemdbluealsaaplayargs),g;

.in:
	$(SED) -e '$(SYSTEMD_SERVICE_SUBS)' < $< > $@
