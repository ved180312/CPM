# frozen_string_literal: true

class AddFloorIdToSlots < ActiveRecord::Migration[7.0]
  def change
    add_column :slots, :floor_id, :integer
  end
end
