# Tank Trouble

    Bài tập môn Lập Trình Nâng Cao - INT2215 22.
    Họ và tên: Vũ Quốc Tuấn.
    Mã sinh viên: 23021711. 

## *Mô tả GAME*

### *Giới thiệu*

* "Tank Trouble" lấy cảm hứng từ game cùng tên do AZTank sản xuất.
* Đến với "Tank Trouble" chúng ta sẽ được điều khiển chiếc xe tăng để chống lại tử thần qua chế độ Single player hoặc so tài với bạn bè qua chế độ Multi player .

### *Cách chơi*


#### 1. Giới thiệu nhân vật
*  **xe tăng 1**  ![player11](https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/9e66db69-a150-4019-9875-f81e2c580d76)

*  **xe tăng 2** ![player12](https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/14394c3e-8fba-4ea2-bb04-9185e7b38013)
  
*  **tử thần**  ![quai2](https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/4e113727-8eca-48a3-ba71-1d1fcbb8894d)

#### 2. Giới thiệu vật phẩm/ đạn
*  **armor** ![Armor](https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/26f2e57f-fb7e-4aa6-868a-f7cf6ceb18d2) cứu người chơi 1 mạng.

*  **rocket** ![Rocket](https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/2bb1a1a6-921c-4e20-ba0b-efd048657935) giúp người chơi bắn ra rocket ![rocket](https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/d41a0999-b0db-41c0-9920-563c7c09a090) tự động đuổi theo mục tiêu.


*  **laser** ![Laser](https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/7cbec12a-010e-44f3-a1b9-2b8e077e6847) giúp người chơi bắn ra laser ![lazer](https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/66eca54d-06db-4e9c-87cb-2025dfa3508c) đi xuyên qua tường.

*  **black hole** ![hole1](https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/01517213-8228-429e-acd6-d196e4ae8168) giúp người chơi dịch chuyển.


#### 4. Các chế độ game
* **Chế độ đơn- Single player:**
  
  <img width="674" alt="Screenshot 2024-05-16 210402" src="https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/48a59f79-b14b-434e-8295-f4a1f2103da3">
  
  <img width="674" alt="Screenshot 2024-05-16 210333" src="https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/2284ac72-8982-4786-84a9-9d32c3782f9e">

* **Chế độ đối kháng- Multiple player:**
  
  <img width="673" alt="Screenshot 2024-05-16 210636" src="https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/099afa55-a519-4a25-94ba-64cff714a400">

  <img width="674" alt="Screenshot 2024-05-16 211943" src="https://github.com/Vu-Quoc-Tuan/TankTrouble/assets/158484347/c1db67b6-a6e1-4fc8-a3fd-bf015f8e620c">



## *Ngưỡng điểm mong muốn 8,5-9,5:*
### *Các kĩ thuật cơ bản:*
*  Sử dụng hình ảnh, âm thanh, text, hiệu ứng vụ nổ.
*  Tạo TileMap và xử lý va chạm
*  Xử lý các thao tác từ bàn phím, chuột
*  Tạo menu, end game , pause, bật tắt âm thanh
*  Sử dụng các công thức toán cơ bản để bắn đạn và di chuyển
*  Có lưu lại điểm cao nhất
  
### *Các kĩ thuật nâng cao:*  
* Làm đạn nảy lại khi đập tường
* Sử dụng thuật toán BFS để tìm đường ngắn nhất đông thời dùng các công thức toán để di chuyển viên đạn
* Có dùng lập trình hướng đối tượng
* Tối giản phần main.cpp



