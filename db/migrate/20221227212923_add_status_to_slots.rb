class AddStatusToSlots < ActiveRecord::Migration[7.0]
  def change
    add_column :slots, :status, :boolean, default: false
  end
end
