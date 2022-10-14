# frozen_string_literal: true

class CreateUserDetails < ActiveRecord::Migration[7.0]
  def change
    create_table :user_details do |t|
      t.string :name
      t.string :email
      t.string :car_color
      t.string :car_number
      t.datetime :in_time
      t.datetime :out_time

      t.timestamps
    end
  end
end
