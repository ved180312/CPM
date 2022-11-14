# frozen_string_literal: true

class CreateCustomerDetails < ActiveRecord::Migration[7.0]
  def change
    create_table :customer_details do |t|
      t.string :name
      t.string :email
      t.string :car_color
      t.string :car_number
      t.datetime :in_time
      t.datetime :out_time
      t.string :confirm

      t.timestamps
    end
  end
end
