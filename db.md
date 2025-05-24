![image](https://github.com/user-attachments/assets/7ea8e6c2-9020-46d8-bbaa-1993f7923c26)

-- Создание таблицы маклеров
CREATE TABLE Brokers (
    broker_id INTEGER PRIMARY KEY AUTOINCREMENT,
    last_name TEXT NOT NULL,
    address TEXT NOT NULL,
    birth_year INTEGER NOT NULL
);

-- Создание таблицы поставщиков
CREATE TABLE Suppliers (
    supplier_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);

-- Создание таблицы покупателей
CREATE TABLE Buyers (
    buyer_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);

-- Создание таблицы товаров
CREATE TABLE Products (
    product_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    type TEXT NOT NULL,
    unit_price REAL NOT NULL,
    supplier_id INTEGER NOT NULL,
    expiration_date TEXT NOT NULL,
    quantity INTEGER NOT NULL,
    FOREIGN KEY (supplier_id) REFERENCES Suppliers(supplier_id)
);

-- Создание таблицы сделок
CREATE TABLE Deals (
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

-- Таблица статистики по маклерам
CREATE TABLE BrokerStatistics (
    broker_id INTEGER PRIMARY KEY,
    total_quantity INTEGER NOT NULL DEFAULT 0,
    total_amount REAL NOT NULL DEFAULT 0,
    FOREIGN KEY (broker_id) REFERENCES Brokers(broker_id)
);

-- Пример данных для Brokers
INSERT INTO Brokers (last_name, address, birth_year) VALUES 
('Иванов', 'ул. Центральная, д.1', 1980),
('Петров', 'ул. Лесная, д.7', 1975);

-- Пример данных для Suppliers
INSERT INTO Suppliers (name) VALUES 
('Фирма А'), ('Фирма Б');

-- Пример данных для Buyers
INSERT INTO Buyers (name) VALUES 
('Покупатель 1'), ('Покупатель 2');

-- Пример данных для Products
INSERT INTO Products (name, type, unit_price, supplier_id, expiration_date, quantity) VALUES 
('Парфюм A', 'Духи', 1200.00, 1, '2025-12-31', 100),
('Парфюм B', 'Туалетная вода', 800.00, 2, '2025-06-30', 200);

-- Пример данных для Deals
INSERT INTO Deals (deal_date, product_id, quantity_sold, broker_id, buyer_id) VALUES 
('2025-05-01', 1, 10, 1, 1),
('2025-05-03', 2, 20, 2, 2);

