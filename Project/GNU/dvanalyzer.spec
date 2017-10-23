# Copyright (c) 2009-2009 zen@mediaarea.net
# This file and all modifications and additions to the pristine
# package are under the same license as the package itself.

# norootforbuild

%define dvanalyzer_version		1.4.2
%define libmediainfo_version	0.7.99
%define libzen_version			0.4.37

Name:			dvanalyzer
Version:		%dvanalyzer_version
Release:		1
Summary:		Supplies technical and tag information about a video or audio file (CLI)
Group:			Productivity/Multimedia/Other
License:		GPL
URL:			http://avpreserve.com/dvanalyzer/
Packager:		Jerome Martinez <zen@mediaarea.net>
Source0:		dvanalyzer_%{version}-1.tar.gz
BuildRoot:		%{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires:	dos2unix
BuildRequires: 	gcc-c++
BuildRequires:	pkgconfig
BuildRequires:  automake
BuildRequires:  autoconf
BuildRequires:  libtool
%if 0%{?suse_version}
BuildRequires:	update-desktop-files
%endif
BuildRequires:	libmediainfo-devel >= %libmediainfo_version
BuildRequires:	libzen-devel >= %libzen_version
BuildRequires: 	zlib-devel
%if 0%{?mageia}
BuildRequires:  sane-backends-iscan
%if 0%{?mageia} >= 6
BuildRequires:  libproxy-pacrunner
%endif
BuildRequires:  libuuid-devel
%endif

Requires:	libzen0 >= %libzen_version
Requires:	libmediainfo0 >= %libmediainfo_version

%description
DV Analyzer CLI (Command Line Interface)

DV Analyzer provides two primary services simultaneously:

Error Detection and Quality Control
The reformatting of DV tapes (such as miniDV, DVCam, and DVCPro) to
DV file-based formats is a point when the introduction of permanent errors
is of particularly high risk. Most capture tools for DV only report errors
if they are significant, such as a lost frame, whereas other documented
errors are not reviewed. DVanalyzer provides a way to analyze and report
audio, video, subcode, and structural errors within a DV file. This enables
automated quality control and the ability to verify the accuracy and
integrity of the reformatting process on a frame-by-frame basis.

Temporal Metadata Reporting
The DV format is rich with temporal metadata. Every frame may contain
time code, recording date and time information, recording markers, and more.
DVanalyzer reports this information which can be used in a variety of
meaningful ways when working with and preserving DV content. This is
particularly useful in documenting source material of edited DV content.

%package gui
Summary:	Supplies technical and tag information about a video or audio file (GUI)
Group:		Productivity/Multimedia/Other

%if 0%{?fedora_version} || 0%{?centos} >= 7
BuildRequires:  pkgconfig(Qt5)
%else
%if 0%{?mageia}
%ifarch x86_64
BuildRequires:  lib64qt5base5-devel
%else
BuildRequires:  libqt5base5-devel
%endif
%else
%if 0%{?suse_version} >= 1200
BuildRequires: libqt5-qtbase-devel
%else
BuildRequires: libqt4-devel
%endif
%endif
%endif

%if 0%{?rhel} >= 7
BuildRequires:  gnu-free-sans-fonts
%endif

%description gui
DV Analyzer GUI (Graphical User Interface)

DV Analyzer provides two primary services simultaneously:

Error Detection and Quality Control
The reformatting of DV tapes (such as miniDV, DVCam, and DVCPro) to
DV file-based formats is a point when the introduction of permanent errors
is of particularly high risk. Most capture tools for DV only report errors
if they are significant, such as a lost frame, whereas other documented
errors are not reviewed. DVanalyzer provides a way to analyze and report
audio, video, subcode, and structural errors within a DV file. This enables
automated quality control and the ability to verify the accuracy and
integrity of the reformatting process on a frame-by-frame basis.

Temporal Metadata Reporting
The DV format is rich with temporal metadata. Every frame may contain
time code, recording date and time information, recording markers, and more.
DVanalyzer reports this information which can be used in a variety of
meaningful ways when working with and preserving DV content. This is
particularly useful in documenting source material of edited DV content.

%prep
%setup -q -n DVAnalyzer
dos2unix     *.txt Release/*.txt
%__chmod 644 *.html *.txt Release/*.txt

%build
export CFLAGS="$RPM_OPT_FLAGS"
export CXXFLAGS="$RPM_OPT_FLAGS"

# build CLI
pushd Project/GNU/CLI
	%__chmod +x autogen
	./autogen
	%if 0%{?mageia} >= 6
		%configure --disable-dependency-tracking
	%else
		%configure
	%endif

	%__make %{?jobs:-j%{jobs}}
popd

# now build GUI
pushd Project/QtCreator
	%__chmod +x prepare
	./prepare BINDIR=%{_bindir}

	%__make %{?jobs:-j%{jobs}}
popd

%install
pushd Project/GNU/CLI
	%__make install DESTDIR=%{buildroot}
popd

pushd Project/QtCreator
	%__make install INSTALL_ROOT=%{buildroot}
popd

# icon
%__install -dm 755 %{buildroot}%{_datadir}/icons/hicolor/128x128/apps
%__install -m 644 Source/Resource/Image/AVPS/logo_sign_alpha_square.png \
	%{buildroot}%{_datadir}/icons/hicolor/128x128/apps/%{name}.png
%__install -dm 755 %{buildroot}%{_datadir}/pixmaps
%__install -m 644 Source/Resource/Image/AVPS/logo_sign_alpha_square.png \
	%{buildroot}%{_datadir}/pixmaps/%{name}.png

# menu-entry
%__install -dm 755 %{buildroot}/%{_datadir}/applications
%__install -m 644 Project/GNU/GUI/dvanalyzer-gui.desktop \
	%{buildroot}/%{_datadir}/applications
%if 0%{?suse_version}
  %suse_update_desktop_file -n dvanalyzer-gui AudioVideo AudioVideoEditing
%endif
%__install -dm 755 %{buildroot}/%{_datadir}/apps/konqueror/servicemenus
%__install -m 644 Project/GNU/GUI/dvanalyzer-gui.kde3.desktop \
	%{buildroot}/%{_datadir}/apps/konqueror/servicemenus/dvanalyzer-gui.desktop
%if 0%{?suse_version}
  %suse_update_desktop_file -n %{buildroot}/%{_datadir}/apps/konqueror/servicemenus/dvanalyzer-gui.desktop AudioVideo AudioVideoEditing
%endif
%__install -dm 755 %{buildroot}/%{_datadir}/kde4/services/ServiceMenus/
%__install -m 644 Project/GNU/GUI/dvanalyzer-gui.kde4.desktop \
	%{buildroot}/%{_datadir}/kde4/services/ServiceMenus/dvanalyzer-gui.desktop
%__install -dm 755 %{buildroot}/%{_datadir}/kservices5/ServiceMenus/
%__install -m 644 Project/GNU/GUI/dvanalyzer-gui.kde4.desktop \
	%{buildroot}/%{_datadir}/kservices5/ServiceMenus/dvanalyzer-gui.desktop
%if 0%{?suse_version}
  %suse_update_desktop_file -n %{buildroot}/%{_datadir}/kde4/services/ServiceMenus/dvanalyzer-gui.desktop AudioVideo AudioVideoEditing
  %suse_update_desktop_file -n %{buildroot}/%{_datadir}/kservices5/ServiceMenus/dvanalyzer-gui.desktop AudioVideo AudioVideoEditing
%endif

%clean
[ -d "%{buildroot}" -a "%{buildroot}" != "" ] && %__rm -rf "%{buildroot}"

%files
%defattr(-,root,root,-)
%doc Release/ReadMe_CLI_Linux.txt
%doc License.html History_CLI.txt
%{_bindir}/dvanalyzer

%files gui
%defattr(-,root,root,-)
%doc Release/ReadMe_GUI_Linux.txt
%doc License.html History_GUI.txt
%{_bindir}/dvanalyzer-gui
%{_datadir}/applications/*.desktop
%{_datadir}/pixmaps/*.png
%dir %{_datadir}/icons/hicolor
%dir %{_datadir}/icons/hicolor/128x128
%dir %{_datadir}/icons/hicolor/128x128/apps
%{_datadir}/icons/hicolor/128x128/apps/*.png
%dir %{_datadir}/apps
%dir %{_datadir}/apps/konqueror
%dir %{_datadir}/apps/konqueror/servicemenus
%{_datadir}/apps/konqueror/servicemenus/*.desktop
%dir %{_datadir}/kde4
%dir %{_datadir}/kde4/services
%dir %{_datadir}/kde4/services/ServiceMenus
%{_datadir}/kde4/services/ServiceMenus/*.desktop
%dir %{_datadir}/kservices5
%dir %{_datadir}/kservices5/ServiceMenus
%{_datadir}/kservices5/ServiceMenus/*.desktop

%changelog
* Tue Jan 01 2009 Jerome Martinez <zen@mediaarea.net> - 1.4.2-0
- See History.txt for more info and real dates

