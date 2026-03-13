# Create a package (in a different way)
pkg: $(DISTDIR).tar.gz

# Create a package archive 
$(DISTDIR).tar.gz: clean $(DISTDIR)
	tar chof - $(DISTDIR) | gzip -9 -c > $@	
	rm -rf $(DISTDIR)
	test -d archives/ || mkdir archives/
	mv $@ archives/

# Create a package directory
$(DISTDIR):
	rm -f $(DISTDIR).tar.gz
	rm -rf $(DISTDIR)
	mkdir -p \
		$(DISTDIR)/bin \
		$(DISTDIR)/include \
		$(DISTDIR)/share \
		$(DISTDIR)/src/android/ \
		$(DISTDIR)/vendor
	cp src/Makefile.in $(DISTDIR)/src/
	cp src/README.md $(DISTDIR)/src/
	cp src/config.h.in $(DISTDIR)/src/
	cp src/lua.c $(DISTDIR)/src/
	cp src/lua.h $(DISTDIR)/src/
	cp src/main.c $(DISTDIR)/src/
	cp src/shared.h $(DISTDIR)/src/
	cp src/zhttp.c $(DISTDIR)/src/
	cp src/zhttp.h $(DISTDIR)/src/
	cp src/zrender.c $(DISTDIR)/src/
	cp src/zrender.h $(DISTDIR)/src/
	cp src/ztable.c $(DISTDIR)/src/
	cp src/ztable.h $(DISTDIR)/src/
	cp src/zwalker.c $(DISTDIR)/src/
	cp src/zwalker.h $(DISTDIR)/src/
	cp -r src/android/* $(DISTDIR)/src/android/

# Check that packaging worked (super useful for other distributions...) 
#pkgcheck:
#	gzip -cd $(DISTDIR).tar.gz | tar xvf -
#	cd $(DISTDIR) && ./configure
#	cd $(DISTDIR) && $(MAKE)
#	cd $(DISTDIR) && $(MAKE) clean
#	rm -rf $(DISTDIR)
#	@echo "*** package $(DISTDIR).tar.gz is ready for distribution."

# pkgclean - Run `clean` in prep for a clean package
pkgclean: veryclean
	-@rm -rf autom4te.cache/ 
	-@rm config.guess config.log config.status config.sub configure

# pkgboot - Run a bootstrapping procedure to initialize autoconf
pkgboot:
	autoupdate && autoreconf --install

