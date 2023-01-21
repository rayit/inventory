# inventory

## Installation

Ubuntu
```bash
sudo apt install mariadb-server
sudo systemctl start mariadb
sudo mysql_secure_installation
sudo apt install libmariadb-dev-compat
sudo apt install glade
```

Void
> Minimal needed
```bash
sudo xbps-install gtk+3-devel-3.24.34_1
sudo xbps-install libmariadbclient-devel-10.5.10_3
sudo xbps-install mariadb-client-10.5.10_3
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
> Build for gtk
```bash
cc `pkg-config --cflags gtk+-3.0 libmariadb` main.c -o inventory `pkg-config --libs gtk+-3.0 libmariadb`
```
