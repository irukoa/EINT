# Maintainer: Alvaro R. Puente-Uriona <irukoa@live.com>
pkgname=eint
_pkgfname=EINT
pkgver=v0.0.1
pkgrel=1
pkgdesc="Numerically integrate data employing the extrapolation method."
arch=('x86_64')
url="https://github.com/irukoa/EINT"
license=('GPLv3')
makedepends=('git' 'gcc-fortran')
source=("git+${url}")
md5sums=('SKIP')

build() {
	cd "$_pkgfname"
	make release
}

package() {
	cd "$_pkgfname"
	make install DESTDIR="$pkgdir" PREFIX="/usr" MNPATH="/usr/local/man"
	install -Dm 644 ./README.md "$pkgdir/usr/share/doc/$pkgname/README.md"
}
