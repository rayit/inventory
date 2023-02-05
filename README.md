# inventory

## Installation

```bash
sudo apt install mariadb-server
sudo systemctl start mariadb
sudo mysql_secure_installation
sudo apt install libmariadb-dev-compat
sudo apt install glade
```
## Design app with Glade

## Database

> Getting started
```sql
CREATE TABLE `Persons` (
  `PersonID` int(11) NOT NULL AUTO_INCREMENT,
  `LastName` varchar(255) DEFAULT NULL,
  `FirstName` varchar(255) DEFAULT NULL,
  `Address` varchar(255) DEFAULT NULL,
  `City` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`PersonID`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci 
```

## Manual
> Build for gtk (manually)
```bash
cc `pkg-config --cflags gtk+-3.0` main.c -o hello `pkg-config --libs gtk+-3.0`
```

> Build with mariadb and gtk3
```bash
cc `pkg-config --cflags gtk+-3.0` `mariadb_config --cflags` main.c Model/person.c -o inventory `pkg-config --libs gtk+-3.0` `mariadb_config --libs`
```

### Windows build

> msys2

> TODO look into:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-x86_64-gtk3
pacman -S mingw-w64-x86_64-toolchain base-devel
pacman -S mingw-w64-x86_64-toolchain base-devel
pacman -S pkg-config
pacman -S clang64/mingw-w64-clang-x86_64-gtkmm3  clang64/mingw-w64-clang-x86_64-wxwidgets3.2-gtk3-libs clang32/mingw-w64-clang-i686-wxwidgets3.2-gtk3-libs  clang32/mingw-w64-clang-i686-gtkmm3
pacman -S clang64/mingw-w64-clang-x86_64-libmariadbclient  ucrt64/mingw-w64-ucrt-x86_64-libmariadbclient
```

```bash
cc `pkg-config --cflags gtk+-3.0` `mariadb_config.exe --cflags`    main.c -o hello `pkg-config.exe --libs gtk+-3.0` `mariadb_config.exe --libs`
```
