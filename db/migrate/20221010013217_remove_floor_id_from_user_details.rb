# frozen_string_literal: true

class RemoveFloorIdFromUserDetails < ActiveRecord::Migration[7.0]
  def change
    remove_column :user_details, :floor_id, :integer
  end
end
