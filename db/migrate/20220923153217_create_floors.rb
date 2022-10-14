# frozen_string_literal: true

class CreateFloors < ActiveRecord::Migration[7.0]
  def change
    create_table :floors do |t|
      t.integer :number_of_floor

      t.timestamps
    end
  end
end
