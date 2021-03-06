%define name glm
%define version 0.3.2
%define release 1

%define name_devel glm-devel

Summary: Alias Wavefront OBJ File Reader/Viewer Library
Name: %name
Version: %version
Release: %release
License: None
Group: System/Libraries
URL: http://devernay.free.fr/hacks/glm/
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: glut-devel

%description
glm is an Alias Wavefront OBJ File Reader/Viewer Library.

%package -n %name_devel
Summary: Development components for glm
Group: System/Libraries
Requires: %name = %version-%release
Provides: glm-devel = %version-%release

%description -n %name_devel
glm is an Alias Wavefront OBJ File Reader/Viewer Library.

This archive contains the header-files for glm development

%prep
%setup -q

%build

%configure --enable-shared --enable-static
make

%install
rm -rf $RPM_BUILD_ROOT
%makeinstall

%post -n %name -p /sbin/ldconfig

%postun -n %name -p /sbin/ldconfig

%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%doc AUTHORS COPYING ChangeLog INSTALL NEWS README TODO
#%_bindir/*
%{_libdir}/*.so.*

%files -n %name_devel
%defattr(-,root,root)
%{_includedir}/*
%_libdir/*.so
%_libdir/*.la
%_libdir/*.a

%changelog
* Wed Oct 13 2004 Frederic Devernay <Frederic.Devernay@inria.fr> - 
- Initial build.

