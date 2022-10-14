# frozen_string_literal: true

class AddFloorIdToUserDetails < ActiveRecord::Migration[7.0]
  def change
    add_column :user_details, :floor_id, :int
  end
end
