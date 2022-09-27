class CreateUserDetails < ActiveRecord::Migration[7.0]
  def change
    create_table :user_details do |t|
      t.string :client_name
      t.string :email
      t.string :car_color
      t.string :car_number
      t.time :in_time
      t.time :out_time
      t.decimal :price

      t.timestamps
    end
  end
end
