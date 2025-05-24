CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password TEXT NOT NULL,
    role TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Brokers (
    broker_id INTEGER PRIMARY KEY AUTOINCREMENT,
    last_name TEXT NOT NULL,
    address TEXT NOT NULL,
    birth_year INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS Suppliers (
    supplier_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Buyers (
    buyer_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Products (
    product_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    type TEXT NOT NULL,
    unit_price REAL NOT NULL,
    supplier_id INTEGER NOT NULL,
    expiration_date TEXT NOT NULL,
    quantity INTEGER NOT NULL,
    image BLOB,
    FOREIGN KEY (supplier_id) REFERENCES Suppliers(supplier_id)
);

CREATE TABLE IF NOT EXISTS Deals (
    deal_id INTEGER PRIMARY KEY AUTOINCREMENT,
    deal_date TEXT NOT NULL,
    product_id INTEGER NOT NULL,
    quantity_sold INTEGER NOT NULL,
    broker_id INTEGER NOT NULL,
    buyer_id INTEGER NOT NULL,
    FOREIGN KEY (product_id) REFERENCES Products(product_id),
    FOREIGN KEY (broker_id) REFERENCES Brokers(broker_id),
    FOREIGN KEY (buyer_id) REFERENCES Buyers(buyer_id)
);

CREATE TABLE IF NOT EXISTS BrokerStatistics (
    broker_id INTEGER PRIMARY KEY,
    total_quantity INTEGER NOT NULL DEFAULT 0,
    total_amount REAL NOT NULL DEFAULT 0,
    FOREIGN KEY (broker_id) REFERENCES Brokers(broker_id)
);

INSERT OR IGNORE INTO users (username, password, role) VALUES 
('admin', 'admin123', 'admin'),
('user', 'user123', 'user');

INSERT OR IGNORE INTO Brokers (last_name, address, birth_year) VALUES 
('Иванов', 'ул. Центральная, д.1', 1980),
('Петров', 'ул. Лесная, д.7', 1975);

INSERT OR IGNORE INTO Suppliers (name) VALUES 
('Фирма А'), ('Фирма Б');

INSERT OR IGNORE INTO Buyers (name) VALUES 
('Покупатель 1'), ('Покупатель 2');

INSERT OR IGNORE INTO Products (name, type, unit_price, supplier_id, expiration_date, quantity) VALUES 
('Парфюм A', 'Духи', 1200.00, 1, '2025-12-31', 100),
('Парфюм B', 'Туалетная вода', 800.00, 2, '2025-06-30', 200);

INSERT OR IGNORE INTO Deals (deal_date, product_id, quantity_sold, broker_id, buyer_id) VALUES 
('2025-05-01', 1, 10, 1, 1),
('2025-05-03', 2, 20, 2, 2);
